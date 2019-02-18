import json
import datetime
import boto3

def lambda_handler(event, context):
    client = boto3.client('iot-data', region_name='us-east-1')
    timestamp = datetime.datetime.now()
    ts = timestamp.strftime("%A %d %B %Y %I:%M:%S%p")
    print(ts)
    payload = json.dumps({'state': { 'desired': { 'feed': 'true' } ,'reported': { 'feed': 'false' } }})

    


    response = client.update_thing_shadow(
        thingName = 'FishFeeder', 
        payload =  payload
        )

    print("IOT response: " + str(response))  
    
    # TODO implement
    return {
        'statusCode': 200,
        'body': json.dumps('Hello from Lambda!')
    }
