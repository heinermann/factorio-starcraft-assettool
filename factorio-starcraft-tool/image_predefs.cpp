#include "image_predefs.h"

std::vector<imagedat_info_t> image_predefs = {
  imagedat_info_t
  {0, false, false, true }, // Scourge
  {1, false, true, true }, // Scourge Shadow
  {2, false, false, false }, // Scourge Birth
  {3, false, false, false }, // Scourge Death
  {4, true, false, false }, // Scourge Explosion
  {5, false, false, true }, // Broodling
  {6, false, true, true }, // Broodling Shadow
  {7, false, false, false }, // Broodling Remnants
  {8, false, false, true }, // Infested Terran
  {9, false, true, true }, // Infested Terran Shadow
  {10, true, false, false }, // Infested Terran Explosion
  {11, false, false, false }, // Guardian Cocoon
  {12, false, true, false }, // Guardian Cocoon Shadow
  {13, false, false, true }, // Defiler
  {14, false, true, true }, // Defiler Shadow
  {15, false, false, false }, // Defiler Birth
  {16, false, false, false }, // Defiler Remnants
  {17, false, false, true }, // Drone
  {18, false, true, true }, // Drone Shadow
  {19, false, false, false }, // Drone Birth
  {20, false, false, false }, // Drone Remnants
  {21, false, false, false }, // Egg
  {22, false, true, false }, // Egg Shadow
  {23, false, false, false }, // Egg Spawn
  {24, false, false, false }, // Egg Remnants
  {25, false, false, true }, // Guardian
  {26, false, true, true }, // Guardian Shadow
  {27, false, false, false }, // Guardian Birth
  {28, false, false, false }, // Guardian Death
  {29, false, false, true }, // Hydralisk
  {30, false, true, true }, // Hydralisk Shadow
  {31, false, false, false }, // Hydralisk Birth
  {32, false, false, false }, // Hydralisk Remnants
  {33, false, false, true }, // Infested Kerrigan
  {34, false, true, true }, // Infested Kerrigan Shadow
  {35, false, false, true }, // Needle Spines
  {36, false, false, true }, // Larva
  {37, false, false, false }, // Larva Remnants
  {38, false, false, true }, // Mutalisk
  {39, false, true, true }, // Mutalisk Shadow
  {40, false, false, false }, // Mutalisk Birth
  {41, false, false, false }, // Mutalisk Death
  {42, false, false, true }, // Overlord
  {43, false, true, true }, // Overlord Shadow
  {44, false, false, false }, // Overlord Birth
  {45, false, false, false }, // Overlord Death
  {46, false, false, true }, // Queen
  {47, false, true, true }, // Queen Shadow
  {48, false, false, false }, // Queen Death
  {49, false, false, false }, // Queen Birth
  {50, false, false, true }, // Ultralisk
  {51, false, true, true }, // Ultralisk Shadow
  {52, false, false, false }, // Ultralisk Birth
  {53, false, false, false }, // Ultralisk Remnants
  {54, false, false, true }, // Zergling
  {55, false, true, true }, // Zergling Shadow
  {56, false, false, false }, // Zergling Birth
  {57, false, false, false }, // Zergling Remnants
  {58, false, false, false }, // Zerg Air Death Explosion (Large)
  {59, false, false, false }, // Zerg Air Death Explosion (Small)
  {60, false, false, false }, // Zerg Building Explosion
  {61, false, false, false }, // Cerebrate
  {62, false, true, false }, // Cerebrate Shadow
  {63, false, false, false }, // Infested Command Center
  {64, false, false, false }, // Spawning Pool
  {65, false, true, false }, // Spawning Pool Shadow
  {66, false, false, false }, // Evolution Chamber
  {67, false, true, false }, // Evolution Chamber Shadow
  {68, false, false, false }, // Creep Colony
  {69, false, true, false }, // Creep Colony Shadow
  {70, false, false, false }, // Hatchery
  {71, false, true, false }, // Hatchery Shadow
  {72, false, false, false }, // Hive
  {73, false, true, false }, // Hive Shadow
  {74, false, false, false }, // Lair
  {75, false, true, false }, // Lair Shadow
  {76, false, false, false }, // Sunken Colony
  {77, false, true, false }, // Sunken Colony Shadow
  {78, false, false, false }, // Mature Chrysalis
  {79, false, true, false }, // Mature Chrysalis Shadow
  {80, false, false, false }, // Greater Spire
  {81, false, true, false }, // Greater Spire Shadow
  {82, false, false, false }, // Defiler Mound
  {83, false, true, false }, // Defiler Mound Shadow
  {84, false, false, false }, // Queen's Nest
  {85, false, true, false }, // Queen Nest Shadow
  {86, false, false, false }, // Nydus Canal
  {87, false, true, false }, // Nydus Canal Shadow
  {88, false, false, false }, // Overmind With Shell
  {89, false, false, false }, // Overmind Remnants
  {90, false, false, false }, // Overmind Without Shell
  {91, false, false, false }, // Ultralisk Cavern
  {92, false, true, false }, // Ultralisk Cavern Shadow
  {93, false, false, false }, // Extractor
  {94, false, true, false }, // Extractor Shadow
  {95, false, false, false }, // Hydralisk Den
  {96, false, true, false }, // Hydralisk Den Shadow
  {97, false, false, false }, // Spire
  {98, false, true, false }, // Spire Shadow
  {99, false, false, false }, // Spore Colony
  {100, false, true, false }, // Spore Colony Shadow
  {101, false, false, false }, // Infested Command Center Overlay
  {102, false, false, false }, // Zerg Construction (Large)
  {103, false, false, false }, // Zerg Building Morph
  {104, false, false, false }, // Zerg Construction (Medium)
  {105, false, false, false }, // Zerg Construction (Small)
  {106, false, true, false }, // Zerg Building Construction Shadow
  {107, false, false, false }, // Zerg Building Spawn (Small)
  {108, false, false, false }, // Zerg Building Spawn (Medium)
  {109, false, false, false }, // Zerg Building Spawn (Large)
  {110, false, false, false }, // Zerg Building Rubble (Small)
  {111, false, false, false }, // Zerg Building Rubble (Large)
  {112, false, false, true }, // Carrier
  {113, false, true, true }, // Carrier Shadow
  {114, true, false, true }, // Carrier Engines
  {116, false, false, true }, // Interceptor
  {117, false, true, true }, // Interceptor Shadow
  {118, false, false, true }, // Shuttle
  {119, false, true, true }, // Shuttle Shadow
  {120, true, false, true }, // Shuttle Engines
  {122, false, false, true }, // Dragoon
  {123, false, true, true }, // Dragoon Shadow
  {124, false, false, false }, // Dragoon Remnants
  {126, false, false, true }, // High Templar
  {127, false, true, true }, // High Templar Shadow
  {129, false, false, true }, // Dark Templar (Hero)
  {130, false, false, true }, // Arbiter
  {131, false, true, true }, // Arbiter Shadow
  {132, true, false, true }, // Arbiter Engines
  {134, true, false, false }, // Archon Energy
  {135, true, false, true }, // Archon Being
  {136, true, false, false }, // Archon Swirl
  {137, false, false, true }, // Probe
  {138, false, true, true }, // Probe Shadow
  {140, false, false, true }, // Scout
  {141, false, true, true }, // Scout Shadow
  {142, true, false, true }, // Scout Engines
  {144, false, false, true }, // Reaver
  {145, false, true, true }, // Reaver Shadow
  {147, false, false, true }, // Scarab
  {148, false, false, true }, // Observer
  {149, false, true, true }, // Observer Shadow
  {151, false, false, true }, // Zealot
  {152, false, true, true }, // Zealot Shadow
  {153, false, false, false }, // Zealot Death
  {155, false, false, false }, // Templar Archives
  {156, true, false, false }, // Templar Archives Warp Flash
  {157, false, true, false }, // Templar Archives Shadow
  {158, false, false, false }, // Assimilator
  {159, true, false, false }, // Assimilator Warp Flash
  {160, false, true, false }, // Assimilator Shadow
  {161, false, false, false }, // Observatory
  {162, true, false, false }, // Observatory Warp Flash
  {163, false, true, false }, // Observatory Shadow
  {164, false, false, false }, // Citadel of Adun
  {165, true, false, false }, // Citadel of Adun Warp Flash
  {166, false, true, false }, // Citadel of Adun Shadow
  {167, false, false, false }, // Forge
  {168, false, false, false }, // Forge Overlay
  {169, true, false, false }, // Forge Warp Flash
  {170, false, true, false }, // Forge Shadow
  {171, false, false, false }, // Gateway
  {172, true, false, false }, // Gateway Warp Flash
  {173, false, true, false }, // Gateway Shadow
  {174, false, false, false }, // Cybernetics Core
  {175, true, false, false }, // Cybernetics Core Warp Flash
  {176, false, false, false }, // Cybernetics Core Overlay
  {177, false, true, false }, // Cybernetics Core Shadow
  {178, false, false, false }, // Khaydarin Crystal Formation
  {179, false, false, false }, // Nexus
  {180, true, false, false }, // Nexus Warp Flash
  {181, true, false, false }, // Nexus Overlay
  {182, false, true, false }, // Nexus Shadow
  {183, false, false, false }, // Photon Cannon
  {184, false, true, false }, // Photon Cannon Shadow
  {185, true, false, false }, // Photon Cannon Warp Flash
  {186, false, false, false }, // Arbiter Tribunal
  {187, true, false, false }, // Arbiter Tribunal Warp Flash
  {188, false, true, false }, // Arbiter Tribunal Shadow
  {189, false, false, false }, // Pylon
  {190, true, false, false }, // Pylon Warp Flash
  {191, false, true, false }, // Pylon Shadow
  {192, false, false, false }, // Robotics Facility
  {193, true, false, false }, // Robotics Facility Warp Flash
  {194, false, true, false }, // Robotics Facility Shadow
  {195, false, false, false }, // Shield Battery
  {196, true, false, false }, // Shield Battery Overlay
  {197, true, false, false }, // Shileld Battery Warp Flash
  {198, false, true, false }, // Shield Battery Shadow
  {199, false, false, false }, // Stargate
  {200, true, false, false }, // Stargate Overlay
  {201, true, false, false }, // Stargate Warp Flash
  {202, false, true, false }, // Stargate Shadow
  {203, false, false, false }, // Stasis Cell/Prison
  {204, false, false, false }, // Robotics Support Bay
  {205, true, false, false }, // Robotics Support Bay Warp Flash
  {206, false, true, false }, // Robotics Support Bay Shadow
  {207, false, false, false }, // Protoss Temple
  {208, false, false, false }, // Fleet Beacon
  {209, true, false, false }, // Fleet Beacon Warp Flash
  {210, true, false, false }, // Warp Texture
  {211, true, false, false }, // Warp Anchor
  {212, false, true, false }, // Fleet Beacon Shadow
  {213, true, false, false }, // Explosion1 (Small)
  {214, true, false, false }, // Explosion1 (Medium)
  {215, true, false, false }, // Explosion (Large)
  {216, false, false, false }, // Protoss Building Rubble (Small)
  {217, false, false, false }, // Protoss Building Rubble (Large)
  {218, false, false, true }, // Battlecruiser
  {219, false, true, true }, // Battlecruiser Shadow
  {220, true, false, true }, // Battlecruiser Engines
  {221, false, false, true }, // Civilian
  {222, false, true, true }, // Civilian Shadow
  {223, false, false, true }, // Dropship
  {224, false, true, true }, // Dropship Shadow
  {225, true, false, true }, // Dropship Engines
  {226, false, false, true }, // Firebat
  {227, false, true, true }, // Firebat Shadow
  {228, false, false, true }, // Ghost
  {229, false, true, true }, // Ghost Shadow
  {230, false, false, false }, // Ghost Remnants
  {231, false, false, false }, // Ghost Death
  {232, true, false, true }, // Nuke Beam
  {233, true, false, false }, // Nuke Target Dot
  {234, false, false, true }, // Goliath Base
  {235, false, false, true }, // Goliath Turret
  {236, false, true, true }, // Goliath Shadow
  {237, false, false, true }, // Sarah Kerrigan
  {238, false, true, true }, // Sarah Kerrigan Shadow
  {239, false, false, true }, // Marine
  {240, false, true, true }, // Marine Shadow
  {241, false, false, false }, // Marine Remnants
  {242, false, false, false }, // Marine Death
  {243, false, false, true }, // Wraith
  {244, false, true, true }, // Wraith Shadow
  {245, true, false, true }, // Wraith Engines
  {246, false, false, false }, // Scanner Sweep
  {247, false, false, true }, // SCV
  {248, false, true, true }, // SCV Shadow
  {249, true, false, true }, // SCV Glow
  {250, false, false, true }, // Siege Tank (Tank) Base
  {251, false, false, true }, // Siege Tank (Tank) Turret
  {252, false, true, true }, // Siege Tank (Tank) Base Shadow
  {253, false, false, false }, // Siege Tank (Siege) Base
  {254, false, false, true }, // Siege Tank (Siege) Turret
  {255, false, true, false }, // Siege Tank (Siege) Base Shadow
  {256, false, false, true }, // Vulture
  {257, false, true, true }, // Vulture Shadow
  {258, false, false, false }, // Spider Mine
  {259, false, true, false }, // Spider Mine Shadow
  {260, false, false, false }, // Science Vessel (Base)
  {261, false, false, true }, // Science Vessel (Turret)
  {262, false, true, false }, // Science Vessel Shadow
  {263, false, false, false }, // Terran Academy
  {264, false, false, false }, // Academy Overlay
  {265, false, true, false }, // Academy Shadow
  {266, false, false, false }, // Barracks
  {267, false, true, false }, // Barracks Shadow
  {268, false, false, false }, // Armory
  {269, false, false, false }, // Armory Overlay
  {270, false, true, false }, // Armory Shadow
  {271, false, false, false }, // Comsat Station
  {272, false, false, false }, // Comsat Station Connector
  {273, false, false, false }, // Comsat Station Overlay
  {274, false, true, false }, // Comsat Station Shadow
  {275, false, false, false }, // Command Center
  {276, false, false, false }, // Command Center Overlay
  {277, false, true, false }, // Command Center Shadow
  {278, false, false, false }, // Supply Depot
  {279, false, false, false }, // Supply Depot Overlay
  {280, false, true, false }, // Supply Depot Shadow
  {281, false, false, false }, // Control Tower
  {282, false, false, false }, // Control Tower Connector
  {283, true, false, false }, // Control Tower Overlay
  {284, false, true, false }, // Control Tower Shadow
  {285, false, false, false }, // Factory
  {286, true, false, false }, // Factory Overlay
  {287, false, true, false }, // Factory Shadow
  {288, false, false, false }, // Covert Ops
  {289, false, false, false }, // Covert Ops Connector
  {290, false, false, false }, // Covert Ops Overlay
  {291, false, true, false }, // Covert Ops Shadow
  {292, false, false, false }, // Ion Cannon
  {293, false, false, false }, // Machine Shop
  {294, false, false, false }, // Machine Shop Connector
  {295, false, true, false }, // Machine Shop Shadow
  {296, false, false, false }, // Missile Turret (Base)
  {297, false, false, true }, // Missile Turret (Turret)
  {298, false, true, false }, // Missile Turret (Base) Shadow
  {299, false, false, false }, // Crashed Batlecruiser
  {300, false, true, false }, // Crashed Battlecruiser Shadow
  {301, false, false, false }, // Physics Lab
  {302, false, false, false }, // Physics Lab Connector
  {303, false, true, false }, // Physics Lab Shadow
  {304, false, false, false }, // Bunker
  {305, false, true, false }, // Bunker Shadow
  {306, true, false, true }, // Bunker Overlay
  {307, false, false, false }, // Refinery
  {308, false, true, false }, // Refinery Shadow
  {309, false, false, false }, // Science Facility
  {310, false, false, false }, // Science Facility Overlay
  {311, false, true, false }, // Science Facility Shadow
  {312, false, false, false }, // Nuclear Silo
  {313, false, false, false }, // Nuclear Silo Connector
  {314, false, false, false }, // Nuclear Silo Overlay
  {315, false, true, false }, // Nuclear Silo Shadow
  {316, false, false, true }, // Nuclear Missile
  {317, false, true, true }, // Nuclear Missile Shadow
  {318, true, false, false }, // Nuke Hit
  {319, false, false, false }, // Starport
  {320, true, false, false }, // Starport Overlay
  {321, false, true, false }, // Starport Shadow
  {322, false, false, false }, // Engineering Bay
  {323, false, false, false }, // Engineering Bay Overlay
  {324, false, true, false }, // Engineering Bay Shadow
  {325, false, false, false }, // Terran Construction (Large)
  {326, false, true, false }, // Terran Construction (Large) Shadow
  {327, false, false, false }, // Terran Construction (Medium)
  {328, false, true, false }, // Terran Construction (Medium) Shadow
  {329, false, false, false }, // Addon Construction
  {330, false, false, false }, // Terran Construction (Small)
  {331, false, true, false }, // Terran Construction (Small) Shadow
  {332, true, false, false }, // Explosion2 (Small)
  {333, true, false, false }, // Explosion2 (Medium)
  {334, true, false, false }, // Building Explosion (Large)
  {335, false, false, false }, // Terran Building Rubble (Small)
  {336, false, false, false }, // Terran Building Rubble (Large)
  {337, true, false, false }, // Dark Swarm
  {338, false, false, true }, // Ragnasaur (Ash)
  {339, false, true, true }, // Ragnasaur (Ash) Shadow
  {340, false, false, true }, // Rhynadon (Badlands)
  {341, false, true, true }, // Rhynadon (Badlands) Shadow
  {342, false, false, true }, // Bengalaas (Jungle)
  {343, false, true, true }, // Bengalaas (Jungle) Shadow
  {344, false, false, false, true }, // Vespene Geyser
  {345, false, false, false, true }, // Vespene Geyser2
  {346, false, true, false, true }, // Vespene Geyser Shadow
  {347, false, false, false, true }, // Mineral Field Type1
  {348, false, true, false, true }, // Mineral Field Type1 Shadow
  {349, false, false, false, true }, // Mineral Field Type2
  {350, false, true, false, true }, // Mineral Field Type2 Shadow
  {351, false, false, false, true }, // Mineral Field Type3
  {352, false, true, false, true }, // Mineral Field Type3 Shadow
  {354, false, false, false }, // Zerg Beacon
  {355, true, false, false }, // Zerg Beacon Overlay
  {356, false, false, false }, // Terran Beacon
  {357, true, false, false }, // Terran Beacon Overlay
  {358, false, false, false }, // Protoss Beacon
  {359, true, false, false }, // Protoss Beacon Overlay
  {361, true, false, false }, // Lockdown Field (Small)
  {362, true, false, false }, // Lockdown Field (Medium)
  {363, true, false, false }, // Lockdown Field (Large)
  {364, true, false, false }, // Stasis Field Hit
  {365, true, false, false }, // Stasis Field (Small)
  {366, true, false, false }, // Stasis Field (Medium)
  {367, true, false, false }, // Stasis Field (Large)
  {368, true, false, false }, // Recharge Shields (Small)
  {369, true, false, false }, // Recharge Shields (Medium)
  {370, true, false, false }, // Recharge Shields (Large)
  {371, true, false, false }, // Defensive Matrix Front (Small)
  {372, true, false, false }, // Defensive Matrix Front (Medium)
  {373, true, false, false }, // Defensive Matrix Front (Large)
  {374, true, false, false }, // Defensive Matrix Back (Small)
  {375, true, false, false }, // Defensive Matrix Back (Medium)
  {376, true, false, false }, // Defensive Matrix Back (Large)
  {377, true, false, false }, // Defensive Matrix Hit (Small)
  {378, true, false, false }, // Defensive Matrix Hit (Medium)
  {379, true, false, false }, // Defensive Matrix Hit (Large)
  {380, true, false, false }, // Irradiate (Small)
  {381, true, false, false }, // Irradiate (Medium)
  {382, true, false, false }, // Irradiate (Large)
  {383, false, false, false }, // Ensnare Cloud
  {384, false, false, false }, // Ensnare Overlay (Small)
  {385, false, false, false }, // Ensnare Overlay (Medium)
  {386, false, false, false }, // Ensnare Overlay (Large)
  {387, false, false, false }, // Plague Cloud
  {388, false, false, false }, // Plague Overlay (Small)
  {389, false, false, false }, // Plague Overlay (Medium)
  {390, false, false, false }, // Plague Overlay (Large)
  {391, true, false, false }, // Recall Field
  {392, false, false, false }, // Flag
  {393, false, false, true }, // Young Chrysalis
  {394, false, false, false }, // Psi Emitter
  {395, false, false, true }, // Data Disc
  {396, false, false, false }, // Khaydarin Crystal
  {397, false, false, true }, // Mineral Chunk Type1
  {398, false, false, true }, // Mineral Chunk Type2
  {399, false, false, true }, // Protoss Gas Orb Type1
  {400, false, false, true }, // Protoss Gas Orb Type2
  {401, false, false, true }, // Zerg Gas Sac Type1
  {402, false, false, true }, // Zerg Gas Sac Type2
  {403, false, false, false }, // Terran Gas Tank Type1
  {404, false, false, false }, // Terran Gas Tank Type2
  {405, false, true, true }, // Mineral Chunk Shadow
  {406, false, true, true }, // Protoss Gas Orb Shadow
  {407, false, true, true }, // Zerg Gas Sac Shadow
  {408, false, true, false }, // Terran Gas Tank Shadow
  {409, false, true, false }, // Data Disk Shadow (Ground)
  {410, false, true, true }, // Data Disk Shadow (Carried)
  {411, false, true, false }, // Flag Shadow (Ground)
  {412, false, true, false }, // Flag Shadow (Carried)
  {413, false, true, false }, // Crystal Shadow (Ground)
  {414, false, true, false }, // Crystal Shadow (Carried)
  {415, false, true, false }, // Young Chrysalis Shadow (Ground)
  {416, false, true, true }, // Young Chrysalis Shadow (Carried)
  {417, false, true, false }, // Psi Emitter Shadow (Ground)
  {418, false, true, false }, // Psi Emitter Shadow (Carried)
  {421, true, false, true }, // FlameThrower
  {422, true, false, false }, // Longbolt/Gemini Missiles Trail
  {423, false, false, false }, // Burrowing Dust
  {424, true, false, false }, // Shield Overlay
  {426, true, false, false }, // Double Explosion
  {427, true, false, false }, // Phase Disruptor Hit
  {428, true, false, false }, // Nuclear Missile Death
  {429, true, false, false }, // Spider Mine Death
  {430, true, false, false }, // Vespene Geyser Smoke1
  {431, true, false, false }, // Vespene Geyser Smoke2
  {432, true, false, false }, // Vespene Geyser Smoke3
  {433, true, false, false }, // Vespene Geyser Smoke4
  {434, true, false, false }, // Vespene Geyser Smoke5
  {435, true, false, false }, // Depleted Vespene Geyser Smoke1 Overlay
  {440, true, false, false }, // Fragmentation Grenade Hit
  {441, false, false, false }, // Grenade Shot Smoke
  {442, false, false, false }, // Anti-Matter Missile Hit
  {443, true, false, false }, // Scarab/Anti-Matter Missile Overlay
  {444, true, false, false }, // Scarab Hit
  {445, true, false, false }, // Cursor Marker
  {446, true, false, true }, // Battlecruiser Attack Overlay
  {447, true, false, false }, // Burst Lasers Hit
  {449, true, false, true }, // High Templar Glow
  {450, true, false, false }, // Flames1 Type1 (Small)
  {451, true, false, false }, // Flames1 Type2 (Small)
  {452, true, false, false }, // Flames1 Type3 (Small)
  {453, true, false, false }, // Flames2 Type3 (Small)
  {454, true, false, false }, // Flames3 Type3 (Small)
  {455, true, false, false }, // Flames4 Type3 (Small)
  {456, true, false, false }, // Flames5 Type3 (Small)
  {457, true, false, false }, // Flames6 Type3 (Small)
  {458, false, false, false }, // Bleeding Variant1 Type1 (Small)
  {459, false, false, false }, // Bleeding Variant1 Type2 (Small)
  {460, false, false, false }, // Bleeding Variant1 Type3 (Small)
  {461, false, false, false }, // Bleeding Variant1 Type4 (Small)
  {462, false, false, false }, // Bleeding Variant2 Type1 (Small)
  {463, false, false, false }, // Bleeding Variant2 Type2 (Small)
  {464, false, false, false }, // Bleeding Variant2 Type3 (Small)
  {465, false, false, false }, // Bleeding Variant2 Type4 (Small)
  {466, true, false, false }, // Flames2 Type1 (Small)
  {467, true, false, false }, // Flames2 Type2 (Small)
  {468, true, false, false }, // Flames7 Type3 (Small)
  {469, true, false, false }, // Flames3 Type1 (Small)
  {470, true, false, false }, // Flames3 Type2 (Small)
  {471, true, false, false }, // Flames8 Type3 (Small)
  {472, true, false, false }, // Flames1 Type1 (Large)
  {473, true, false, false }, // Flames1 Type2 (Large)
  {474, true, false, false }, // Flames1 Type3 (Large)
  {475, true, false, false }, // Flames2 Type3 (Large)
  {476, true, false, false }, // Flames3 Type3 (Large)
  {477, true, false, false }, // Flames4 Type3 (Large)
  {478, true, false, false }, // Flames5 Type3 (Large)
  {479, true, false, false }, // Flames6 Type3 (Large)
  {480, false, false, false }, // Bleeding Variant1 Type1 (Large)
  {481, false, false, false }, // Bleeding Variant1 Type2 (Large)
  {482, false, false, false }, // Bleeding Variant1 Type3 (Large)
  {483, false, false, false }, // Bleeding Variant1 Type4 (Large)
  {484, false, false, false }, // Bleeding Variant2 Type1 (Large)
  {485, false, false, false }, // Bleeding Variant2 Type3 (Large)
  {486, false, false, false }, // Bleeding Variant3 Type3 (Large)
  {487, false, false, false }, // Bleeding Variant2 Type4 (Large)
  {488, true, false, false }, // Flames2 Type1 (Large)
  {489, true, false, false }, // Flames2 Type2 (Large)
  {490, true, false, false }, // Flames7 Type3 (Large)
  {491, true, false, false }, // Flames3 Type1 (Large)
  {492, true, false, false }, // Flames3 Type2 (Large)
  {493, true, false, false }, // Flames8 Type3 (Large)
  {494, false, false, false }, // Building Landing Dust Type1
  {495, false, false, false }, // Building Landing Dust Type2
  {496, false, false, false }, // Building Landing Dust Type3
  {497, false, false, false }, // Building Landing Dust Type4
  {498, false, false, false }, // Building Landing Dust Type5
  {499, false, false, false }, // Building Lifting Dust Type1
  {500, false, false, false }, // Building Lifting Dust Type2
  {501, false, false, false }, // Building Lifting Dust Type3
  {502, false, false, false }, // Building Lifting Dust Type4
  {503, false, false, false }, // White Circle
  {504, true, false, false }, // Needle Spine Hit
  {506, false, false, false }, // Sunken Colony Tentacle
  {509, true, false, false }, // Acid Spore
  {510, true, false, false }, // Acid Spore Hit
  {511, false, false, false }, // Glave Wurm
  {512, true, false, false }, // Glave Wurm/Seeker Spores Hit
  {513, true, false, false }, // Glave Wurm Trail
  {514, true, false, false }, // Seeker Spores Overlay
  {515, false, false, false }, // Seeker Spores
  {516, false, false, false }, // Queen Spell Holder
  {517, true, false, false }, // Consume
  {518, true, false, true }, // Guardian Attack Overlay
  {519, true, false, false }, // Dual Photon Blasters Hit
  {520, true, false, false }, // Particle Beam Hit
  {521, false, false, true }, // Anti-Matter Missile
  {522, true, false, true }, // Pulse Cannon
  {523, true, false, false }, // Phase Disruptor
  {524, true, false, false }, // STA/STS Photon Cannon Overlay
  {525, true, false, false }, // Psionic Storm
  {526, true, false, false }, // Fusion Cutter Hit
  {527, true, false, false }, // Gauss Rifle Hit
  {528, false, false, true }, // Gemini Missiles
  {529, false, false, true }, // Lockdown/LongBolt/Hellfire Missile
  {530, true, false, false }, // Gemini Missiles Explosion
  {531, true, false, false }, // C-10 Canister Rifle Hit
  {532, false, false, false }, // Fragmentation Grenade
  {533, true, false, false }, // Arclite Shock Cannon Hit
  {534, true, false, true }, // ATS/ATA Laser Battery
  {535, true, false, true }, // Burst Lasers
  {536, true, false, true }, // Siege Tank(Tank) Turret Attack Overlay
  {537, true, false, true }, // Siege Tank(Siege) Turret Attack Overlay
  {538, true, false, false }, // Science Vessel Overlay (Part1)
  {539, true, false, false }, // Science Vessel Overlay (Part2)
  {540, true, false, false }, // Science Vessel Overlay (Part3)
  {541, true, false, true }, // Yamato Gun
  {542, true, false, true }, // Yamato Gun Trail
  {543, true, false, false }, // Yamato Gun Overlay
  {544, true, false, false }, // Yamato Gun Hit
  {545, true, false, false }, // Hallucination Hit
  {546, true, false, false }, // Scanner Sweep Hit
  {548, true, false, false }, // Psionic Shockwave Hit
  {549, true, false, true }, // Archon Beam
//  {550, true, false, false }, // Psionic Storm Part1
//  {551, true, false, false }, // Psionic Storm Part2
//  {552, true, false, false }, // Psionic Storm Part3
//  {553, true, false, false }, // Psionic Storm Part4
  {554, false, false, true }, // EMP Shockwave Missile
  {555, true, false, false }, // EMP Shockwave Hit (Part1)
  {556, true, false, false }, // EMP Shockwave Hit (Part2)
  {557, true, false, false }, // Hallucination Death1
  {558, true, false, false }, // Hallucination Death2
  {559, true, false, false }, // Hallucination Death3
//  {561, true, false, false }, // Selection Circle (22pixels)
//  {562, true, false, false }, // Selection Circle (32pixels)
//  {563, true, false, false }, // Selection Circle (48pixels)
//  {564, true, false, false }, // Selection Circle (62pixels)
//  {565, true, false, false }, // Selection Circle (72pixels)
//  {566, true, false, false }, // Selection Circle (94pixels)
//  {567, true, false, false }, // Selection Circle (110pixels)
//  {568, true, false, false }, // Selection Circle (122pixels)
//  {569, true, false, false }, // Selection Circle (146pixels)
//  {570, true, false, false }, // Selection Circle (224pixels)
//  {571, true, false, false }, // Selection Circle Dashed (22pixels)
//  {572, true, false, false }, // Selection Circle Dashed (32pixels)
//  {573, true, false, false }, // Selection Circle Dashed (48pixels)
//  {574, true, false, false }, // Selection Circle Dashed (62pixels)
//  {575, true, false, false }, // Selection Circle Dashed (72pixels)
//  {576, true, false, false }, // Selection Circle Dashed (94pixels)
//  {577, true, false, false }, // Selection Circle Dashed (110pixels)
//  {578, true, false, false }, // Selection Circle Dashed (122pixels)
//  {579, true, false, false }, // Selection Circle Dashed (146pixels)
//  {580, true, false, false }, // Selection Circle Dashed (224pixels)
  {582, false, false, false }, // Map Revealer
//  {584, true, false, false }, // Psi Field1 (Right Upper)
//  {585, true, false, false }, // Psi Field1 (Right Lower)
//  {586, true, false, false }, // Psi Field2 (Right Upper)
//  {587, true, false, false }, // Psi Field2 (Right Lower)
//  {588, false, false, false }, // Start Location
//  {589, false, false, false }, // 2/38 Ash
//  {590, false, true, false }, // 2/38 Ash Shadow
//  {591, false, false, false }, // 2/39 Ash
//  {592, false, true, false }, // 2/39 Ash Shadow
//  {593, false, false, false }, // 2/41 Ash
//  {594, false, true, false }, // 2/41 Ash Shadow
//  {595, false, false, false }, // 2/40 Ash
//  {596, false, true, false }, // 2/40 Ash Shadow
//  {597, false, false, false }, // 2/42 Ash
//  {598, false, true, false }, // 2/42 Ash Shadow
//  {599, false, false, false }, // 2/43 Ash
//  {600, false, false, false }, // 2/44 Ash
//  {601, false, false, false }, // 2/1 Ash
//  {602, false, false, false }, // 2/4 Ash
//  {603, false, false, false }, // 2/5 Ash
//  {604, false, false, false }, // 2/30 Ash
//  {605, false, false, false }, // 2/28 Ash
//  {606, false, false, false }, // 2/29 Ash
//  {607, false, false, false }, // 4/1 Ash
//  {608, false, false, false }, // 4/2 Ash
//  {609, false, false, false }, // 4/3 Ash
//  {610, false, false, false }, // 4/56 Jungle
//  {611, false, true, false }, // 4/56 Jungle Shadow
//  {612, false, false, false }, // 4/57 Jungle
//  {613, false, true, false }, // 4/57 Jungle Shadow
//  {614, false, false, false }, // 4/58 Jungle
//  {615, false, true, false }, // 4/58 Jungle Shadow
//  {616, false, false, false }, // 4/59 Jungle
//  {617, false, true, false }, // 4/59 Jungle Shadow
//  {618, false, false, false }, // 9/5 Jungle
//  {619, false, true, false }, // 9/5 Jungle Shadow
//  {620, false, false, false }, // 9/6 Jungle
//  {621, false, true, false }, // 9/6 Jungle Shadow
//  {622, false, false, false }, // 9/7 Jungle
//  {623, false, true, false }, // 9/7 Jungle Shadow
//  {624, false, false, false }, // 4/51 Jungle
//  {625, false, true, false }, // 4/51 Jungle Shadow
//  {626, false, false, false }, // 4/52 Jungle
//  {627, false, true, false }, // 4/52 Jungle Shadow
//  {628, false, false, false }, // 4/54 Jungle
//  {629, false, true, false }, // 4/54 Jungle Shadow
//  {630, false, false, false }, // 4/53 Jungle
//  {631, false, true, false }, // 4/53 Jungle Shadow
//  {632, false, false, false }, // 9/1 Jungle
//  {633, false, true, false }, // 9/1 Jungle Shadow
//  {634, false, false, false }, // 9/2 Jungle
//  {635, false, true, false }, // 9/2 Jungle Shadow
//  {636, false, false, false }, // 9/3 Jungle
//  {637, false, true, false }, // 9/3 Jungle Shadow
//  {638, false, false, false }, // 9/4 Jungle
//  {639, false, true, false }, // 9/4 Jungle Shadow
//  {640, false, false, false }, // 4/12 Jungle
//  {641, false, false, false }, // 4/13 Jungle
//  {642, false, false, false }, // 4/1 Jungle
//  {643, false, false, false }, // 4/3 Jungle
//  {644, false, false, false }, // 4/2 Jungle
//  {645, false, false, false }, // 4/5 Jungle
//  {646, false, false, false }, // 4/4 Jungle
//  {647, false, false, false }, // 4/9 Jungle
//  {648, false, false, false }, // 4/10 Jungle
//  {649, false, false, false }, // 5/5 Jungle
//  {650, false, false, false }, // 5/7 Jungle
//  {651, false, false, false }, // 5/6 Jungle
//  {652, false, false, false }, // 5/9 Jungle
//  {653, false, false, false }, // 5/8 Jungle
//  {654, false, false, false }, // 4/6 Jungle
//  {655, false, false, false }, // 4/7 Jungle
//  {656, false, false, false }, // 4/17 Jungle
//  {657, false, false, false }, // 13/4 Jungle
//  {658, false, false, false }, // 11/5 Jungle
//  {659, false, false, false }, // 11/6 Jungle
//  {660, false, false, false }, // 11/7 Jungle
//  {661, false, false, false }, // 11/8 Jungle
//  {662, false, false, false }, // 11/10 Jungle
//  {663, false, false, false }, // 11/11 Jungle
//  {664, false, false, false }, // 11/12 Jungle
//  {665, false, false, false }, // 7/4 Platform
//  {666, false, true, false }, // 7/4 Platform Shadow
//  {667, false, false, false }, // 7/5 Platform
//  {668, false, true, false }, // 7/5 Platform Shadow
//  {669, false, false, false }, // 7/6 Platform
//  {670, false, true, false }, // 7/6 Platform Shadow
//  {671, false, false, false }, // 7/1 Platform
//  {672, false, true, false }, // 7/1 Platform Shadow
//  {673, false, false, false }, // 7/2 Platform
//  {674, false, true, false }, // 7/2 Platform Shadow
//  {675, false, false, false }, // 7/3 Platform
//  {676, false, true, false }, // 7/3 Platform Shadow
//  {677, false, false, false }, // 7/9 Platform
//  {678, false, false, false }, // 7/10 Platform
//  {679, false, false, false }, // 7/8 Platform
//  {680, false, false, false }, // 7/7 Platform
//  {681, false, false, false }, // 7/26 Platform
//  {682, false, false, false }, // 7/24 Platform
//  {683, false, false, false }, // 7/28 Platform
//  {684, false, false, false }, // 7/27 Platform
//  {685, false, false, false }, // 7/25 Platform
//  {686, false, false, false }, // 7/29 Platform
//  {687, false, false, false }, // 7/30 Platform
//  {688, false, false, false }, // 7/31 Platform
//  {689, false, false, false }, // 12/1 Platform
//  {690, false, false, false }, // 9/27 Platform
//  {691, false, false, false }, // 5/54 Badlands
//  {692, false, true, false }, // 5/54 Badlands Shadow
//  {693, false, false, false }, // 5/55 Badlands
//  {694, false, true, false }, // 5/55 Badlands Shadow
//  {695, false, false, false }, // 5/56 Badlands
//  {696, false, true, false }, // 5/56 Badlands Shadow
//  {697, false, false, false }, // 5/57 Badlands
//  {698, false, true, false }, // 5/57 Badlands Shadow
//  {699, false, false, false }, // 6/16 Badlands
//  {700, false, false, false }, // 6/17 Badlands
//  {701, false, false, false }, // 6/20 Badlands
//  {702, false, false, false }, // 6/21 Badlands
//  {703, false, false, false }, // 5/10 Badlands
//  {704, false, false, false }, // 5/50 Badlands
//  {705, false, true, false }, // 5/50 Badlands Shadow
//  {706, false, false, false }, // 5/52 Badlands
//  {707, false, true, false }, // 5/52 Badlands Shadow
//  {708, false, false, false }, // 5/53 Badlands
//  {709, false, true, false }, // 5/53 Badlands Shadow
//  {710, false, false, false }, // 5/51 Badlands
//  {711, false, true, false }, // 5/51 Badlands Shadow
//  {712, false, false, false }, // 6/3 Badlands
//  {713, false, false, false }, // 11/3 Badlands
//  {714, false, false, false }, // 11/8 Badlands
//  {715, false, false, false }, // 11/6 Badlands
//  {716, false, false, false }, // 11/7 Badlands
//  {717, false, false, false }, // 11/9 Badlands
//  {718, false, false, false }, // 11/10 Badlands
//  {719, false, false, false }, // 11/11 Badlands
//  {720, false, false, false }, // 11/12 Badlands
//  {721, false, false, false }, // 11/13 Badlands
//  {722, false, false, false }, // 11/14 Badlands
//  {723, false, false, false }, // 1/13 Badlands
//  {724, false, false, false }, // 1/9 Badlands
//  {725, false, false, false }, // 1/11 Badlands
//  {726, false, false, false }, // 1/14 Badlands
//  {727, false, false, false }, // 1/10 Badlands
//  {728, false, false, false }, // 1/12 Badlands
//  {729, false, false, false }, // 1/15 Badlands
//  {730, false, false, false }, // 1/7 Badlands
//  {731, false, false, false }, // 1/5 Badlands
//  {732, false, false, false }, // 1/16 Badlands
//  {733, false, false, false }, // 1/8 Badlands
//  {734, false, false, false }, // 1/6 Badlands
  {735, false, false, false }, // Floor Gun Trap
  {736, false, false, false }, // Floor Missile Trap
  {737, false, false, true }, // Floor Missile Trap Turret
  {738, false, false, false }, // Wall Missile Trap
  {739, false, false, false }, // Wall Missile Trap2
  {740, false, false, false }, // Wall Flame Trap
  {741, false, false, false }, // Wall Flame Trap2
  {742, false, false, false }, // Left Upper Level Door
  {743, false, false, false }, // Right Upper Level Door
  //{744, false, false, false }, // 4/15 Installation1
  //{745, false, false, false }, // 4/15 Installation2
  //{746, false, false, false }, // 3/9 Installation
  //{747, false, false, false }, // 3/10 Installation
  //{748, false, false, false }, // 3/11 Installation
  //{749, false, false, false }, // 3/12 Installation
  {750, false, false, false }, // Substructure Left Door
  {751, false, false, false }, // Substructure Right Door
  //{752, false, false, false }, // 3/1 Installation
  //{753, false, false, false }, // 3/2 Installation
  {754, false, false, false }, // Substructure Opening Hole
 // {755, false, false, false }, // 7/21 Twilight
 // {756, false, false, false }, // Unknown Twilight
 // {757, false, false, false }, // 7/13 Twilight
 // {758, false, false, false }, // 7/14 Twilight
 // {759, false, false, false }, // 7/16 Twilight
 // {760, false, false, false }, // 7/15 Twilight
 // {761, false, false, false }, // 7/19 Twilight
 // {762, false, false, false }, // 7/20 Twilight
 // {763, false, false, false }, // 7/17 Twilight
 // {764, false, false, false }, // 6/1 Twilight
 // {765, false, false, false }, // 6/2 Twilight
 // {766, false, false, false }, // 6/3 Twilight
 // {767, false, false, false }, // 6/4 Twilight
 // {768, false, false, false }, // 6/5 Twilight
 // {769, false, false, false }, // 8/3 Twilight1
 // {770, false, false, false }, // 8/3 Twilight2
 // {771, false, false, false }, // 9/29 Ice
 // {772, false, true, false }, // 9/29 Ice Shadow
 // {773, false, false, false }, // 9/28 Ice
 // {774, false, true, false }, // 9/28 Ice Shadow
 // {775, false, false, false }, // 12/38 Ice
 // {776, false, true, false }, // 12/38 Ice Shadow
 // {777, false, false, false }, // 12/37 Ice
 // {778, false, true, false }, // 12/37 Ice Shadow
 // {779, false, false, false }, // 12/33 Ice1
 // {780, false, true, false }, // 12/33 Ice1 Shadow
 // {781, false, false, false }, // 9/21 Ice
 // {782, false, true, false }, // 9/21 Ice Shadow
 // {783, false, false, false }, // 9/15 Ice
 // {784, false, true, false }, // 9/15 Ice Shadow
 // {785, false, false, false }, // 9/16 Ice
 // {786, false, true, false }, // 9/16 Ice Shadow
 // {787, false, false, false }, // Unknown787
 // {788, false, false, false }, // Unknown788
 // {789, false, false, false }, // 12/9 Ice1
 // {790, false, false, false }, // 12/10 Ice1
 // {791, false, false, false }, // 9/24 Ice
 // {792, false, true, false }, // 9/24 Ice Shadow
 // {793, false, false, false }, // 9/23 Ice
 // {794, false, true, false }, // 9/23 Ice Shadow
 // {795, false, false, false }, // Unknown795
 // {796, false, true, false }, // Unknown Ice Shadow
 // {797, false, false, false }, // 12/7 Ice
 // {798, false, true, false }, // 12/7 Ice Shadow
 // {799, false, false, false }, // 12/8 Ice
 // {800, false, true, false }, // 12/8 Ice Shadow
 // {801, false, false, false }, // 12/9 Ice2
 // {802, false, true, false }, // 12/9 Ice2 Shadow
 // {803, false, false, false }, // 12/10 Ice2
 // {804, false, true, false }, // 12/10 Ice2 Shadow
 // {805, false, false, false }, // 12/40 Ice
 // {806, false, true, false }, // 12/40 Ice Shadow
 // {807, false, false, false }, // 12/41 Ice
 // {808, false, true, false }, // 12/41 Ice Shadow
 // {809, false, false, false }, // 12/42 Ice
 // {810, false, true, false }, // 12/42 Ice Shadow
 // {811, false, false, false }, // 12/5 Ice
 // {812, false, true, false }, // 12/5 Ice Shadow
 // {813, false, false, false }, // 12/6 Ice
 // {814, false, true, false }, // 12/6 Ice Shadow
 // {815, false, false, false }, // 12/36 Ice
 // {816, false, true, false }, // 12/36 Ice Shadow
 // {817, false, false, false }, // 12/32 Ice
 // {818, false, true, false }, // 12/32 Ice Shadow
 // {819, false, false, false }, // 12/33 Ice2
 // {820, false, true, false }, // 12/33 Ice2 Shadow
 // {821, false, false, false }, // 12/34 Ice
 // {822, false, true, false }, // 12/34 Ice Shadow
 // {823, false, false, false }, // 12/24 Ice1
 // {824, false, true, false }, // 12/24 Ice1 Shadow
 // {825, false, false, false }, // 12/25 Ice1
 // {826, false, true, false }, // 12/25 Ice1 Shadow
 // {827, false, false, false }, // 12/30 Ice1
 // {828, false, true, false }, // 12/30 Ice1 Shadow
 // {829, false, false, false }, // 12/31 Ice
 // {830, false, true, false }, // 12/31 Ice Shadow
 // {831, false, false, false }, // 12/20 Ice
 // {832, false, false, false }, // 12/30 Ice2
 // {833, false, true, false }, // 12/30 Ice2 Shadow
 // {834, false, false, false }, // 9/22 Ice
 // {835, false, true, false }, // 9/22 Ice Shadow
 // {836, false, false, false }, // 12/24 Ice2
 // {837, false, true, false }, // 12/24 Ice2 Shadow
 // {838, false, false, false }, // 12/25 Ice2
 // {839, false, true, false }, // 12/25 Ice2 Shadow
 // {840, false, false, false }, // Unknown840
 // {841, false, false, false }, // 4/1 Ice
 // {842, false, false, false }, // 6/1 Ice
 // {843, false, false, false }, // 5/6 Ice
 // {844, false, true, false }, // 5/6 Ice Shadow
 // {845, false, false, false }, // 5/7 Ice
 // {846, false, true, false }, // 5/7 Ice Shadow
 // {847, false, false, false }, // 5/8 Ice
 // {848, false, true, false }, // 5/8 Ice Shadow
 // {849, false, false, false }, // 5/9 Ice
 // {850, false, true, false }, // 5/9 Ice Shadow
 // {851, false, false, false }, // 10/10 Desert1
 // {852, false, false, false }, // 10/12 Desert1
 // {853, false, true, false }, // 10/12 Desert1 Shadow
 // {854, false, false, false }, // 10/8 Desert1
 // {855, false, true, false }, // 10/8 Desert1 Shadow
 // {856, false, false, false }, // 10/9 Desert1
 // {857, false, true, false }, // 10/9 Desert1 Shadow
 // {858, false, false, false }, // 6/10 Desert
 // {859, false, true, false }, // 6/10 Desert Shadow
 // {860, false, false, false }, // 6/13 Desert1
 // {861, false, true, false }, // 6/13 Desert1 Shadow
 // {862, false, false, false }, // Unknown Desert
 // {863, false, true, false }, // Unknown Desert Shadow
 // {864, false, false, false }, // 10/12 Desert2
 // {865, false, true, false }, // 10/12 Desert2 Shadow
 // {866, false, false, false }, // 10/9 Desert2
 // {867, false, true, false }, // 10/9 Desert2 Shadow
 // {868, false, false, false }, // 10/10 Desert2
 // {869, false, true, false }, // 10/10 Desert2 Shadow
 // {870, false, false, false }, // 10/11 Desert
 // {871, false, true, false }, // 10/11 Desert Shadow
 // {872, false, false, false }, // 10/14 Desert
 // {873, false, true, false }, // 10/14 Desert Shadow
 // {874, false, false, false }, // 10/41 Desert
 // {875, false, true, false }, // 10/41 Desert Shadow
 // {876, false, false, false }, // 10/39 Desert
 // {877, false, true, false }, // 1/39 Desert Shadow
 // {878, false, false, false }, // 10/8 Desert2
 // {879, false, true, false }, // 10/8 Desert2 Shadow
 // {880, false, false, false }, // 10/6 Desert
 // {881, false, false, false }, // 10/7 Desert
 // {882, false, true, false }, // 10/7 Desert Shadow
 // {883, false, false, false }, // 4/6 Desert
 // {884, false, true, false }, // 4/6 Desert Shadow
 // {885, false, false, false }, // 4/11 Desert
 // {886, false, true, false }, // 4/11 Desert Shadow
 // {887, false, false, false }, // 4/10 Desert
 // {888, false, true, false }, // 4/10 Desert Shadow
 // {889, false, false, false }, // 4/9 Desert
 // {890, false, false, false }, // 4/7 Desert
 // {891, false, true, false }, // 4/7 Desert Shadow
 // {892, false, false, false }, // 4/12 Desert
 // {893, false, true, false }, // 4/12 Desert Shadow
 // {894, false, false, false }, // 4/8 Desert
 // {895, false, false, false }, // 4/13 Desert
 // {896, false, true, false }, // 4/13 Desert Shadow
 // {897, false, false, false }, // 4/17 Desert
 // {898, false, false, false }, // 4/15 Desert1
 // {899, false, true, false }, // 4/15 Desert1 Shadow
 // {900, false, false, false }, // 10/23 Desert
 // {901, false, true, false }, // 10/23 Desert Shadow
 // {902, false, false, false }, // 10/5 Desert
 // {903, false, true, false }, // 10/5 Desert Shadow
 // {904, false, false, false }, // 6/13 Desert2
 // {905, false, true, false }, // 6/13 Desert2 Shadow
 // {906, false, false, false }, // 6/20 Desert
 // {907, false, false, false }, // 4/15 Desert2
 // {908, false, true, false }, // 4/15 Desert2 Shadow
 // {909, false, false, false }, // 8/23 Desert
 // {910, false, true, false }, // 8/23 Desert Shadow
 // {911, false, false, false }, // 12/1 Desert Overlay
 // {912, false, false, false }, // 11/3 Desert
  {914, false, false, false }, // Lurker Egg
  {915, false, false, true }, // Devourer
  {916, false, true, true }, // Devourer Shadow
  {917, false, false, false }, // Devourer Birth
  {918, false, false, false }, // Devourer Death
  {919, false, false, false }, // Lurker Birth
  {920, false, false, false }, // Lurker Remnants
  {921, false, false, true }, // Lurker
  {922, false, true, true }, // Lurker Shadow
  {923, false, false, false }, // Overmind Cocoon
  {924, false, true, false }, // Overmind Cocoon Shadow
  {925, true, false, false }, // Dark Archon Energy
  {926, true, false, true }, // Dark Archon Being
  {927, true, false, false }, // Dark Archon Swirl
  {928, true, false, false }, // Dark Archon Death
  {929, false, false, true }, // Corsair
  {930, false, true, true }, // Corsair Shadow
  {931, true, false, true }, // Corsair Engines
  {933, false, false, true }, // Dark Templar (Unit)
  {934, false, false, false }, // Warp Gate
  {935, false, true, false }, // Warp Gate Shadow
  {936, true, false, false }, // Warp Gate Overlay
  {937, false, false, false }, // Xel'Naga Temple
  {938, false, true, false }, // Xel'Naga Temple Shadow
  {939, false, false, true }, // Valkyrie
  {940, false, true, true }, // Valkyrie Shadow
  {941, true, false, true }, // Valkyrie Engines
  {944, false, false, true }, // Medic
  {945, false, true, true }, // Medic Shadow
  {946, false, false, false }, // Medic Remnants
  {947, false, false, false }, // Psi Disrupter
  {948, false, true, false }, // Psi Disrupter Shadow
  {949, false, false, false }, // Power Generator
  {950, false, true, false }, // Power Generator Shadow
  {951, true, false, false }, // Disruption Web
  {952, false, false, true }, // Scantid (Desert)
  {953, false, true, true }, // Scantid (Desert) Shadow
  {954, false, false, true }, // Kakaru (Twilight)
  {955, false, true, true }, // Kakaru (Twilight) Shadow
  {956, false, false, true }, // Ursadon (Ice)
  {957, false, true, true }, // Ursadon (Ice) Shadow
  {958, false, false, false }, // Uraj
  {959, false, false, false }, // Khalis
  {960, true, false, false }, // Halo Rockets Trail
  {961, false, false, false }, // Subterranean Spines
  {962, false, false, true }, // Corrosive Acid Shot
  {963, false, false, false }, // Corrosive Acid Hit
  {964, true, false, false }, // Neutron Flare
  {965, false, false, true }, // Halo Rockets
  {966, false, false, false }, // Optical Flare Grenade
  {967, true, false, false }, // Restoration Hit (Small)
  {968, true, false, false }, // Restoration Hit (Medium)
  {969, true, false, false }, // Restoration Hit (Large)
  {973, true, false, false }, // Mind Control Hit (Small)
  {974, true, false, false }, // Mind Control Hit (Medium)
  {975, true, false, false }, // Mind Control Hit (Large)
  {976, true, false, false }, // Optical Flare Hit (Small)
  {977, true, false, false }, // Optical Flare Hit (Medium)
  {978, true, false, false }, // Optical Flare Hit (Large)
  {979, true, false, false }, // Feedback (Small)
  {980, true, false, false }, // Feedback (Medium)
  {981, true, false, false }, // Feedback Hit (Large)
  {982, true, false, false }, // Maelstorm Overlay (Small)
  {983, true, false, false }, // Maelstorm Overlay (Medium)
  {984, true, false, false }, // Maelstorm Overlay (Large)
  {986, false, false, false }, // Acid Spores (1-9) Overlay (Small)
  {990, false, false, false }, // Acid Spores (1-9) Overlay (Medium)
  {994, false, false, false }, // Acid Spores (1-9) Overlay (Large)
  {998, true, false, false } // Maelstorm Hit
};

