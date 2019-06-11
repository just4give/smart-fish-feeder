import json
import datetime
import boto3

def lambda_handler(event, context):
    client = boto3.client('iot-data', region_name='us-east-1')
    sns = boto3.client('sns')
    timestamp = datetime.datetime.now()
    ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")
    print(ts)
    #payload = json.dumps({'state': { 'desired': { 'feed': 'true' } ,'reported': { 'feed': 'false' } }})

    


    response = client.get_thing_shadow(
        thingName = 'FishFeeder'
        )

    streamingBody = response["payload"]
    jsonState = json.loads(streamingBody.read())
 
    print (jsonState)
    print (jsonState["state"]["reported"]["feed"])
    
    feeded=jsonState["state"]["reported"]["feed"]
    
    if feeded != 'true':
        sns.publish(
            TopicArn='arn:aws:sns:us-east-1:xxxxx:fish-feeder-alert',
            Message='Error. Your smart feeder did not run.',
            Subject='FishFeeder',
        )
    else:
        sns.publish(
            TopicArn='arn:aws:sns:us-east-1:xxxxx:fish-feeder-alert',
            Message='Success. fishes were feeded.',
            Subject='FishFeeder',
        )
    
    
    # TODO implement
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
