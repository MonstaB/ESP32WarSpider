
Project: War Spider
Specification Version: v0.0.0-1
Initial Hardware: M5Stack Cardputer-Adv + Cap LoRa-1262/868
Development Platform: Arduino IDE 2.x / Espressif ESP32 Arduino framework
First Firmware Version: v0.0.1
Target Standalone Release: v0.1.0
Long-Term Goal: Distributed War Spider Web for WDGWARS players

1. Project Vision

War Spider is a modular, distributed wardriving and wireless observation system designed around the concept of a Spider.

A Spider consists of:

A Body/Host — the M5Stack Cardputer-Adv.
Zero to eight Legs — external compatible execution/scanning nodes.
Optional communication with other Spiders, forming a Web.

The fundamental architecture is:

The Body thinks. The Legs execute. The Web coordinates.

A Spider with zero Legs is a completely valid Spider.

A Spider with one or more Legs gains additional scanning capability.

Multiple Spiders can communicate and coordinate to form a Web.

Captured observation data is not automatically shared between Spiders.

2. Terminology
2.1 Spider

One complete War Spider unit.

SPIDER
 └── BODY
      ├── LEG 1
      ├── LEG 2
      ├── ...
      └── LEG 8

A Spider may contain zero to eight Legs.

2.2 Body / Host

The M5Stack Cardputer-Adv is the Body.

The Body is the intelligent component of the Spider.

The Body is responsible for:

User interface
Configuration
Storage
GPS
Wireless observation
LoRa communication
Leg management
Task assignment
Team coordination
Web coordination
Data management
Export

The Body must remain fully functional without any Legs.

2.3 Leg / Node

A Leg is a War Spider-compatible execution/scanning device.

A Leg is a functional role, not a specific hardware model.

Possible Leg hardware includes:

LilyGO T-Dongle / ESP32-S3
ESP32-C5 modules
ESP32-C6 modules
Future compatible hardware

The architecture must never assume that every Leg uses identical hardware.

A Leg is intentionally a relatively dumb device.

Its primary responsibilities are:

Receive instructions.
Execute instructions.
Report status.
Report capabilities.
Return observations.
Continue its assigned task until instructed otherwise.

A Leg does not make high-level decisions about how the Spider or Web should operate.

2.4 Web

A Web consists of multiple Spiders communicating and coordinating with each other.

             WEB
              │
      ┌───────┼───────┐
      │       │       │
   SPIDER   SPIDER   SPIDER
      A       B       C

The Web allows multiple Bodies to coordinate available scanning resources.

A Web must never be required for a single Spider to function.

3. Core Architecture

The system is deliberately divided into three levels.

Leg

Execute.

Body

Manage and operate.

Web

Coordinate.

This separation is a fundamental architectural rule.

The Web should not directly control the hardware of another Spider's Legs.

Instead:

WEB
 ↓
BODY
 ↓
LEG

The Body remains responsible for its own Legs.

4. Hardware Identity

Every physical Body must have a permanent:

DEVICE_ID

This identifies the physical device.

It must remain separate from configurable information such as:

SPIDER_NAME
TEAM_ID
SESSION_ID

For example:

DEVICE_ID  = permanent hardware identity
SPIDER_NAME = Spider-01
TEAM_ID     = TEAM-A
SESSION_ID  = current session

Changing the Spider's name or team must not change its hardware identity.

Legs should similarly have a permanent hardware identity:

LEG_DEVICE_ID

A Body may additionally assign a local:

LEG_ID

These are separate concepts.

5. User Configuration

User-configurable information may include:

SPIDER_NAME
TEAM_ID
SESSION_ID
TEAM_SETTINGS
RADIO_SETTINGS
SCAN_SETTINGS

Configuration must not overwrite permanent hardware identity.

6. Team Identity and Security

TEAM_ID identifies a logical team.

It must not itself be treated as a secret key.

The security architecture will distinguish between:

DEVICE_ID
TEAM_ID
TEAM_KEY / TEAM_CREDENTIALS

Team credentials will eventually provide authentication and confidentiality.

Sensitive team information must not be transmitted as plaintext.

The exact cryptographic protocol will be designed and tested before implementation.

7. Team Communication

Team communication is intended for coordination between trusted Spiders.

Possible team information includes:

Spider presence
Team membership
Authentication state
Spider identity
GPS position where enabled
Leg availability
Leg capabilities
Current assignments
Channel allocation
Spider status
Web membership
Connection state

Team coordination information is separate from captured observation data.

8. Captured Data Privacy

Captured observations are not automatically shared simply because two Spiders:

Are on the same team
Come within range
Detect each other
Communicate over LoRa

Normal operation is:

Spider A
   ↓
captures observations
   ↓
stores locally

Spider B does not automatically receive Spider A's observation database.

This is an intentional design requirement.

9. Optional Spider-to-Spider Data Synchronisation

Captured data synchronisation is an explicit user-triggered operation.

Players may choose to synchronise their data when they gather together.

Example:

Spider A                 Spider B
    │                        │
    │       meet             │
    │                        │
    └────── SYNC ────────────┘
              ↓
       compare records
              ↓
       exchange missing
        observations

The purpose is to allow players to:

Maintain personal records
Merge team records
Combine observations from multiple Spiders
Create a unified local dataset

Synchronisation does not mean uploading the data.

External uploads remain a separate user action.

10. Observation Data

War Spider will maintain its own internal observation model.

The internal model must not be designed around a particular external website.

An observation may eventually contain:

Observation ID
Spider ID
Leg ID
Session ID
Timestamp
GPS position
Observation type
Observed identifier
Observed name
Signal information
Additional metadata

The exact schema will be defined during implementation.

11. Observation Identity and Deduplication

Every observation must have a mechanism for identifying it uniquely.

This will be required for:

Duplicate detection
Recovery
Synchronisation
Database imports
Historical tracking

The system must eventually distinguish between:

The same observation being received twice

and:

The same target being observed multiple times

The exact rules will be defined when the observation database is designed.

12. Internal Data vs Export Data

War Spider's internal storage must remain independent of external CSV formats.

The architecture is:

                 WAR SPIDER DATA
                       │
          ┌────────────┼────────────┐
          │            │            │
       WiGLE        WDGWARS     Other formats
       Export        Export

External formats are export adapters.

This prevents external format requirements from dictating the internal database design.

13. Existing Wardriver Database Compatibility

Compatibility with the existing wardriver database/importer project is a deliberate requirement.

The eventual War Spider export must be capable of being consumed by the existing importers that currently accept compatible Bruce/wardriver data.

The desired flow is:

War Spider
    ↓
capture
    ↓
internal data
    ↓
War Spider export
    ↓
existing importer
    ↓
existing wardriver database

The goal is that the existing importer can accept War Spider data without requiring the existing database architecture to be rewritten.

In particular:

If replacing Bruce with War Spider in the existing importer is not straightforward, the War Spider export format is not considered complete.

14. WiGLE / WDGWARS Export

War Spider will eventually produce compatible CSV exports for the required external services.

The architecture is:

Capture
   ↓
Internal storage
   ↓
Optional Spider synchronisation
   ↓
User chooses export
   ↓
CSV
   ↓
WiGLE / WDGWARS

Export is always a deliberate user action.

15. Legs — Quantity

A Body supports:

0–8 Legs

The Body must work correctly with any number of Legs from zero through eight.

Examples:

0 Legs → standalone Spider

1 Leg → one distributed scanner

2 Legs → two distributed scanners

4 Legs → four distributed scanners

8 Legs → maximum local configuration

The software must never assume that eight Legs exist.

16. Legs — Hardware Independence

The Leg protocol must be hardware-independent.

A Body may encounter:

LEG 01 → ESP32-S3 T-Dongle
LEG 02 → ESP32-C5
LEG 03 → ESP32-C6
LEG 04 → future hardware

The Body must communicate with all of them through the common War Spider Leg protocol.

The Body must not contain hard-coded assumptions such as:

if hardware == T-Dongle

for fundamental Leg operation.

Hardware-specific capabilities are discovered from the Leg.

17. Leg Capability Discovery

When a Leg connects, it should introduce itself.

Conceptually:

LEG HELLO

LEG_DEVICE_ID: <permanent identity>
LEG_ID:        <local identity>

HARDWARE:      ESP32-C6
FIRMWARE:      0.0.1
PROTOCOL:      1

RADIOS:
    WIFI
        2.4 GHz
        5 GHz
        6 GHz

    BLUETOOTH
        BLE

CAPABILITIES:
    WIFI_SCAN
    BLE_SCAN

The exact packet structure will be defined later.

The fundamental principle is:

The Body asks the Leg what it can do instead of assuming what it can do.

18. Radio Capability Model

Radio capabilities must be independent from current assignments.

For example:

CAPABILITY:
    Wi-Fi 2.4 GHz

CURRENT TASK:
    channels 1–4

A Leg might support:

2.4 GHz
5 GHz

while another may support:

2.4 GHz
5 GHz
6 GHz

The Body and eventually the Web must know the difference.

This will allow the Web to reason about actual available scanning resources.

19. Leg Capability Expansion

The capability system must be extensible.

Future capabilities might include:

WIFI_2G4
WIFI_5G
WIFI_6G
BLE
OTHER_RADIO
GPS
SPECIAL_SENSOR

The exact capability identifiers will be defined later.

The important requirement is that adding new Leg hardware must not require redesigning the entire Body architecture.

20. Leg Intelligence

Legs do not make strategic decisions.

A Leg does not decide:

Which channels to scan
Which channels another Leg should scan
What another Spider is doing
How the team should divide channels
When the Web should reorganise
Which Spider should perform a task

Those decisions belong to the Body/Web.

A Leg may report:

I support 2.4 GHz
I support 5 GHz
I am currently scanning channels 1–4
I found X observations

But it does not decide what it should scan next.

21. Leg Task Model

The Body assigns tasks to Legs.

A task may eventually contain:

Task ID
Radio
Band
Channel
Channel range
Channel set
Scan mode
Timing
Other parameters

For example:

TASK

TYPE: CHANNEL_RANGE
BAND: 2.4 GHz
START: 1
END: 4

Or:

TASK

TYPE: CHANNEL_SET
BAND: 2.4 GHz
CHANNELS: 1, 6, 11

The Leg executes the task.

22. Persistent Leg Tasks

A Leg continues its last valid task until:

The Body sends a new valid task.
The user stops the Leg.
A hardware/software failure occurs.
A defined safety condition occurs.

If communication is temporarily lost:

continue current task

is the default behaviour.

A Leg must not invent a new task because it has temporarily lost communication with its Body.

23. Command IDs

Body-to-Leg commands must have unique command/sequence IDs.

Example:

COMMAND 1042
      ↓
Leg receives
      ↓
Leg acknowledges
      ↓
Leg executes
      ↓
Leg reports:
COMMAND 1042 ACTIVE

This allows the system to handle:

Lost commands
Duplicate commands
Retransmissions
Command confirmation
Current task state
24. Local Body-to-Leg Communication

The initial local communication system will use ESP-NOW.

             BODY
              │
           ESP-NOW
              │
      ┌───────┼───────┐
      │       │       │
    LEG 1   LEG 2   LEG 3 ...

Up to eight Legs may be connected.

The ESP-NOW layer is separate from the Spider-to-Spider Web communication layer.

25. Spider-to-Spider Communication

Multiple Bodies will communicate using the Cap LoRa-1262/868 hardware.

Conceptually:

Spider A
    ↕
  LoRa
    ↕
Spider B
    ↕
  LoRa
    ↕
Spider C

LoRa communication is a Web-level function.

The Body remains operational if LoRa is unavailable.

26. Short-Range Team LoRa

The intended team communication configuration is optimised for local team coordination.

The initial target configuration is:

Spreading Factor: SF6
Bandwidth:        500 kHz
Transmit Power:   2 dBm

The goal is to create a relatively local communication bubble rather than maximise long-distance LoRa range.

Actual range will be experimentally measured rather than assumed.

Radio configuration must remain configurable.

27. Team Communication Security

Team communication should eventually provide:

Team authentication
Confidential team messages
Protection against unauthorised participation
Replay protection
Message integrity

Sensitive information such as team GPS positions must not be readable by unauthorised listeners.

The exact cryptographic design will be selected and documented before implementation.

28. Dynamic Channel Allocation

A major purpose of the Web is to distribute scanning resources efficiently.

For example:

Spider A
    Leg 1 → 2.4 GHz channels 1–4
    Leg 2 → 2.4 GHz channels 5–8

Spider B
    Leg 1 → 2.4 GHz channels 9–11
    Leg 2 → 2.4 GHz channels 12–14

The allocation system must consider:

Number of Spiders
Number of Legs
Leg capabilities
Supported bands
Current assignments
Relative proximity
Spider availability
Communication status
29. Proximity-Based Coordination

The Web may use relative Spider proximity to optimise scanning.

When Spiders are close together, scanning resources can be divided more aggressively.

As Spiders separate, assignments can change to improve geographic coverage.

An initial conceptual close-range threshold is approximately:

30 metres

However, this must remain configurable and experimentally validated.

The architecture must not be permanently built around one exact distance.

30. GPS

The Cap's ATGM336H GNSS hardware provides GPS/GNSS information.

GPS will eventually provide:

Position
UTC time
Fix status
Position quality
Observation timestamps
Spider location for team coordination

Possible states:

INITIALISING
SEARCHING
FIXED
LOST

GPS loss must not disable the Spider.

31. Time

The system should distinguish between:

GPS UTC time
Device uptime
Session time
Observation time

GPS time should be preferred where an authoritative timestamp is available.

Device uptime remains useful for diagnostics and recovery.

32. Storage

The SD card is the primary removable storage medium.

Captured observations must be stored locally before optional synchronisation or export.

CSV does not have to be the primary internal storage format.

Internal storage should support:

Large observation sets
Interrupted sessions
Duplicate detection
Synchronisation
Recovery
Future schema changes
33. Storage Failure

SD card failure must not automatically crash the entire Spider.

The system should:

Detect the failure.
Inform the user.
Log the failure where possible.
Continue unrelated functionality where practical.
Eventually support buffering/recovery.
34. Sessions

Observations should belong to a session.

A session may contain:

SESSION_ID
START_TIME
END_TIME
TEAM_ID
SPIDER_ID

Session identity is separate from permanent hardware identity.

A Spider may participate in many sessions during its lifetime.

35. Configuration and Data Separation

Configuration and observation data must be separated.

Conceptually:

/config/
    configuration

/data/
    sessions
    observations

/export/
    generated exports

The final filesystem layout will be decided during implementation.

36. Factory Reset

Configuration reset and observation deletion must be separate operations.

For example:

RESET CONFIGURATION

must not automatically mean:

DELETE ALL OBSERVATIONS

These should be separate explicit actions.

37. Diagnostics

War Spider should eventually have a hardware diagnostic system.

Potential Body tests:

DISPLAY       PASS/FAIL
KEYBOARD      PASS/FAIL
SD CARD       PASS/FAIL
GPS           PASS/FAIL
WIFI          PASS/FAIL
LORA          PASS/FAIL
BATTERY       PASS/FAIL
ESP-NOW       PASS/FAIL

Leg diagnostics should eventually include:

LEG CONNECTION
LEG HARDWARE
LEG FIRMWARE
LEG PROTOCOL
RADIO CAPABILITIES
CURRENT TASK
38. Logging

System/developer logging and captured observations must remain separate.

Example:

[INFO] War Spider starting
[INFO] Display OK
[INFO] SD OK
[INFO] GPS initialising
[INFO] LoRa initialising

The UI must not become the system logging mechanism.

39. Hardware Abstraction

Hardware-specific operations must be isolated.

The application should not contain Cardputer-specific hardware code throughout the entire project.

The architecture should be:

Application
     ↓
Services
     ↓
Hardware Interfaces
     ↓
Cardputer / Cap Hardware

The same principle applies to Legs:

Body Services
     ↓
Leg Protocol
     ↓
Leg Hardware

This allows ESP32-S3, C5, C6, and future hardware to coexist.

40. UI Architecture

The UI is a presentation layer.

It displays system state but does not own the underlying systems.

UI
 ↓
Services
 ↓
GPS / Storage / Wi-Fi / LoRa / Legs / Web

Keyboard actions should request operations from the appropriate service.

41. Versioning

War Spider will use incremental development versions.

There is no artificial limit to the number of development versions.

For example:

v0.0.1
v0.0.2
v0.0.3
...
v0.0.50
...
v0.1.0

is completely acceptable.

Each meaningful development stage should produce a known-good checkpoint.

42. Specification Versioning

The project specification itself is versioned independently from firmware.

The first specification is:

v0.0.0-1

This means:

The architectural starting point of the project.

Later specification changes may be recorded as:

v0.0.0-2
v0.0.0-3
...

or a new specification milestone when appropriate.

Firmware versions remain independent:

Specification: v0.0.0-1
Firmware:      v0.0.1
43. Development Philosophy

Development will proceed in small, testable increments.

The preferred rule is:

One meaningful change. One test. One known-good checkpoint.

We deliberately do not care if reaching v0.1.0 takes:

20 versions
50 versions
100 versions

or more.

Early development prioritises:

Correctness
Reliability
Understandability
Testability
Recovery
Features
Appearance

A simple reliable firmware is preferable to a feature-rich firmware with poorly understood behaviour.

44. M5Launcher

M5Launcher should remain installed on the Cardputer-Adv.

The preferred development/testing workflow is:

Arduino IDE
    ↓
Compile War Spider
    ↓
Generate firmware .bin
    ↓
Copy to SD card
    ↓
M5Launcher
    ↓
Select War Spider
    ↓
Test

Direct USB flashing remains available as a development/recovery method but is not intended to be required for normal firmware testing.

Previous known-good War Spider builds should remain available through M5Launcher where practical.

45. Source Control

The project will use Git from the beginning.

GitHub will be the primary remote repository.

The first repository content will be this specification.

The initial repository state is:

WAR_SPIDER_PROJECT_SPECIFICATION.md

Specification version:

v0.0.0-1

Every meaningful stable firmware milestone should be committed.

Important firmware versions should be tagged:

v0.0.1
v0.0.2
v0.0.3
...
46. Repository Documentation

The repository should eventually contain:

README.md

WAR_SPIDER_PROJECT_SPECIFICATION.md

CHANGELOG.md

/docs/
    architecture
    protocols
    hardware
    database
    export formats
    testing

/src/
    firmware source

/examples/
    development examples

The exact structure will evolve as the project grows.

47. Reproducible Development

The project must document its development environment.

This includes:

Arduino IDE version
ESP32 board package version
Required libraries
Library versions where important
Target hardware
Hardware revisions
Build settings

Initial intended libraries include:

M5Cardputer
TinyGPS++
RadioLib

Additional libraries should only be introduced when there is a clear requirement.

48. Testing Philosophy

Testing is incremental.

For hardware:

Initialise
   ↓
Test
   ↓
Verify
   ↓
Known-good
   ↓
Add next component

For storage:

Write
 ↓
Close
 ↓
Reopen
 ↓
Read
 ↓
Verify

For communication:

Send
 ↓
Receive
 ↓
Validate
 ↓
Acknowledge
 ↓
Execute

For Legs:

Discover
 ↓
Identify
 ↓
Read capabilities
 ↓
Assign task
 ↓
Execute
 ↓
Report
49. Recovery Philosophy

The system must assume failures will occur.

Potential failures include:

Power loss
SD failure
GPS loss
LoRa loss
ESP-NOW loss
Leg disappearance
Spider disappearance
Interrupted synchronisation
Firmware errors

The system should degrade gracefully.

Examples:

Web disappears
    ↓
Spider continues operating

Leg disappears
    ↓
Body continues operating

GPS disappears
    ↓
Scanning continues

SD problem
    ↓
User is warned and unrelated functions continue where possible

Sync interrupted
    ↓
Local data remains safe
50. Data Synchronisation Principles

Synchronisation should be:

Optional
User-triggered
Incremental where practical
Duplicate-aware
Interruptible
Recoverable

The preferred model is:

Compare
   ↓
Determine missing records
   ↓
Exchange missing records
   ↓
Verify
   ↓
Complete

The system should avoid blindly copying complete databases when only a subset of records is required.

51. External Upload Separation

War Spider must distinguish between:

CAPTURE
SYNC
EXPORT
UPLOAD

These are four different operations.

Capture

Record observations.

Sync

Optionally exchange observations between Spiders.

Export

Generate an external-compatible file.

Upload

The user independently chooses whether to upload the exported file.

War Spider must not automatically upload captured data.

52. Long-Term Architecture

The intended final structure is:

                         WAR SPIDER WEB
                              │
             ┌────────────────┼────────────────┐
             │                │                │
          SPIDER A         SPIDER B         SPIDER C
             │                │                │
        ┌────┼────┐      ┌────┼────┐      ┌────┼────┐
        │    │    │      │    │    │      │    │    │
       LEG  LEG  LEG    LEG  LEG  LEG    LEG  LEG  LEG

Each Body remains independently functional.

Each Leg remains deliberately simple.

The Web coordinates Bodies.

The Web considers the actual capabilities of the Legs available to it.

53. Development Priority

Development will proceed approximately as follows:

v0.0.x
    ↓
Cardputer foundation
    ↓
Display
    ↓
Keyboard
    ↓
Configuration
    ↓
System logging
    ↓
SD
    ↓
GPS
    ↓
Wi-Fi observation
    ↓
Observation storage
    ↓
Data validation
    ↓
Export
    ↓
Standalone Spider
    ↓
v0.1.0

After v0.1.0:

ESP-NOW
    ↓
First compatible Leg
    ↓
Leg discovery
    ↓
Leg capability reporting
    ↓
Leg task protocol
    ↓
One working Leg
    ↓
Multiple Leg hardware types
    ↓
Multiple Legs
    ↓
LoRa Spider-to-Spider communication
    ↓
Team authentication/encryption
    ↓
Web membership
    ↓
GPS team coordination
    ↓
Dynamic resource/channel allocation
    ↓
Proximity-based coordination
    ↓
Optional Spider synchronisation
    ↓
Full Spider Web

This is a guide, not a restriction.

Additional versions should be created whenever doing so makes the code easier to test and understand.

54. Fundamental Design Rules

These rules form the architectural contract of War Spider.

A Body must work with zero Legs.
A Body supports up to eight Legs.
A Leg is a functional role, not a specific hardware platform.
Legs may use ESP32-S3, ESP32-C5, ESP32-C6, or future compatible hardware.
The Body discovers Leg capabilities instead of assuming them.
Radio capabilities such as 2.4 GHz, 5 GHz, and 6 GHz must be identifiable.
Legs execute instructions; they do not make high-level decisions.
A Leg continues its last valid task until instructed otherwise.
A Body remains functional without Legs.
A Spider remains functional without other Spiders.
A Web enhances Spiders; it does not make them dependent on each other.
Permanent hardware identity is separate from user configuration.
Team identity is separate from hardware identity.
TEAM_ID is not itself a secret encryption key.
Sensitive team communication requires authentication and encryption.
Captured observation data is not automatically shared between Spiders.
Captured-data synchronisation is explicitly user-triggered.
External uploads are explicitly user-triggered.
Internal observation data is independent from external CSV formats.
Existing wardriver importer compatibility is a deliberate requirement.
Replacing Bruce with War Spider in the existing importer should be straightforward.
CSV is an export format, not necessarily the primary storage format.
Important protocols and data structures must support versioning.
Failures should degrade gracefully.
Development should favour small, testable, known-good steps.
M5Launcher remains available as the normal firmware selection/recovery environment.
Hardware-specific code must remain isolated.
New Leg hardware should be addable without redesigning the Body.
The Web coordinates resources rather than directly owning another Spider's Legs.
The architecture must remain extensible for future radio bands and hardware.
55. First Firmware Milestone — v0.0.1

The first firmware is intentionally tiny.

Requirements
Power on
    ↓
ESP32 boots
    ↓
Cardputer display initialises
    ↓
Display:

WAR SPIDER
v0.0.1

HELLO WORLD

Nothing else is required.

No:

GPS
SD
Wi-Fi scanning
LoRa
ESP-NOW
Legs
Web
Final UI

The purpose of v0.0.1 is to establish the first known-good War Spider firmware and prove the complete development cycle:

Source
 ↓
Git
 ↓
Arduino IDE
 ↓
Compile
 ↓
Firmware
 ↓
SD card
 ↓
M5Launcher
 ↓
Cardputer
 ↓
Boot
 ↓
Verify

From that point onward, War Spider grows one verified step at a time.

56. Project Motto

The Body thinks.
The Legs execute.
The Web coordinates.

And:

One Spider works alone. Many Spiders make the Web.
