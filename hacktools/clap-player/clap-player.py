#!/usr/bin/env python
# This hack reads amplitude from microphone which when goes
# beyond a threshold changes song, using cmus-remote.
# - Rohit Yadav <rohityadav89@gmail.com>

import alsaaudio, audioop, time
from subprocess import call

#Change here your clap amplitude, or from microphone input level
clap_amplitude = 28000

def main():
  inp = alsaaudio.PCM(alsaaudio.PCM_CAPTURE,alsaaudio.PCM_NONBLOCK)
  # Set attributes: Mono, 8000 Hz, 16 bit little endian samples
  inp.setchannels(1)
  inp.setrate(8000)
  inp.setformat(alsaaudio.PCM_FORMAT_S16_LE)
  inp.setperiodsize(160)

  # Loop forever, look for claps
  while True:
    # Read data from device
    l,data = inp.read()
    if l:
        if audioop.max(data, 2) > 28000:
          call(['cmus-remote', '-n'])
          print "Song changed | Amp:", audioop.max(data,2)
    time.sleep(.01)

if __name__ == "__main__":
  main()
