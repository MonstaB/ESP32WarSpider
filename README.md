# ESP32WarSpider
Cardputer Wardriver
still building 

Version	Milestone

v0.0.6  ✅  PlatformIO migration + Cap LoRa + working GPS

v0.0.7  ✅  Session object + session ID + session creation/start + GPS session timestamp

v0.0.8   ✅   Observation data structure

v0.0.9   ✅   Create observation in RAM

v0.0.10  ✅   SD storage foundation

New v 0.0.1 1✅ write manual sessions and WiGLE CSV



v0.0.11     Write one observation to CSV

v0.0.12     Read session CSV / verify stored observations

v0.0.13     Session + observations persisted together

v0.0.14     Wi-Fi observation subsystem skeleton

v0.0.15     Capture real Wi-Fi observations

v0.0.16     GPS snapshot attached to observations

v0.0.17     Observation + GPS association

v0.0.18     Basic session UI

v0.0.19     Session close

v0.0.20     Clean shutdown / session finalisation

v0.0.21     End-to-end field test and fixes

v0.1.0      All acceptance tests pass together


is what we are working towards for now



acceptance contract


✅ Permanent Device ID

✅ Persistent Spider Name

✅ Persistent Team ID

✅ Subsystem framework

✅ GPS subsystem

✅ GPS fix/status

✅ Session creation

Observation data structure

SD storage

Wi-Fi observation

Observation + GPS association

Basic session UI

Clean shutdown/session close

session produces a usable self-contained CSV on SD from v0.1.0.
Automatic uploading remains outside v0.1.0; manua

l removal/upload of the CSV is supported from the first field-capable release.