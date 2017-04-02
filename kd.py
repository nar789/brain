import os
import sys
import asyncio
import subprocess

from google.cloud import speech

proc=subprocess.Popen('sox -t waveaudio default --channels=1 --bits=16 --rate=16000 --encoding=signed-integer c:/brain/k.wav',shell=False)
client = speech.Client()
print("Connextion.")
ret=""
with open('c:/brain/k.wav', 'rb') as stream:
    sample = client.sample(stream=stream,
    encoding=speech.Encoding.LINEAR16,
    sample_rate=16000)
    results = sample.streaming_recognize(language_code='ko-KR',
        single_utterance=False,interim_results=True)
    for result in results:
        for alternative in result.alternatives:
            print('=' * 20)
            ret=alternative.transcript
            print('transcript: ' + ret)
            print('confidence: ' + str(alternative.confidence))

proc.terminate()
proc.wait()
print(ret)
f = open("c:/brain/input.txt", 'w')
f.write(ret)
f.close()
proc=subprocess.Popen('brain')