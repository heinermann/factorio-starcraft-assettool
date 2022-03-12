#include "image_predefs.h"

const imagedat_info_t WARP_TEXTURE{210, true, false, 0, false };

std::vector<imagedat_info_t> image_predefs = {
  imagedat_info_t
  {0, false, false, 5 }, // Scourge
  {2, false, false, 0, false }, // Scourge Birth
  {3, false, false, 0, false }, // Scourge Death
  {4, true, false, 0, false }, // Scourge Explosion
  {5, false, false, 12 }, // Broodling
  {7, false, false }, // Broodling Remnants
  {8, false, false, 8 }, // Infested Terran
  {10, true, false }, // Infested Terran Explosion
  {11, false, false, 0, false }, // Guardian Cocoon
  {13, false, false, 8 }, // Defiler
  {15, false, false, 0, false }, // Defiler Birth
  {16, false, false }, // Defiler Remnants
  {17, false, false, 10 }, // Drone
  {19, false, false, 0, false }, // Drone Birth
  {20, false, false }, // Drone Remnants
  {21, false, false, 0, false }, // Egg
  {23, false, false }, // Egg Spawn
  {24, false, false, 0, false }, // Egg Remnants
  {25, false, false, 7 }, // Guardian
  //{27, false, false }, // Guardian Birth
  {28, false, false, 0, false }, // Guardian Death
  {29, false, false, 12 }, // Hydralisk
  {31, false, false, 0, false }, // Hydralisk Birth
  {32, false, false }, // Hydralisk Remnants
  {33, false, false, 16 }, // Infested Kerrigan
  {35, false, false, 7 }, // Needle Spines
  {36, false, false, 5 }, // Larva
  {37, false, false }, // Larva Remnants
  {38, false, false, 5 }, // Mutalisk
  {40, false, false, 0, false }, // Mutalisk Birth
  {41, false, false, 0, false }, // Mutalisk Death
  {42, false, false, 4 }, // Overlord
  {44, false, false, 0, false }, // Overlord Birth
  {45, false, false, 0, false }, // Overlord Death
  {46, false, false, 11 }, // Queen
  {48, false, false, 0, false }, // Queen Death
  {49, false, false, 0, false }, // Queen Birth
  {50, false, false, 15 }, // Ultralisk
  {52, false, false, 0, false }, // Ultralisk Birth
  {53, false, false }, // Ultralisk Remnants
  {54, false, false, 12 }, // Zergling
  {56, false, false, 0, false }, // Zergling Birth
  {57, false, false }, // Zergling Remnants
  {58, false, false, 0, false }, // Zerg Air Death Explosion (Large)
  {59, false, false, 0, false }, // Zerg Air Death Explosion (Small)
  {60, false, false, 0, false }, // Zerg Building Explosion
  {61, false, false, 0, false }, // Cerebrate
  {63, false, false, 0, false }, // Infested Command Center
  {64, false, false, 0, false }, // Spawning Pool
  {66, false, false, 0, false }, // Evolution Chamber
  {68, false, false, 0, false }, // Creep Colony
  {70, false, false, 0, false }, // Hatchery
  {72, false, false, 0, false }, // Hive
  {74, false, false, 0, false }, // Lair
  {76, false, false, 0, false }, // Sunken Colony
  {78, false, false, 0, false }, // Mature Chrysalis
  {80, false, false, 0, false }, // Greater Spire
  {82, false, false, 0, false }, // Defiler Mound
  {84, false, false, 0, false }, // Queen's Nest
  {86, false, false, 0, false }, // Nydus Canal
  {88, false, false, 0, false }, // Overmind With Shell
  {89, false, false, 0, false }, // Overmind Remnants
  //{90, false, false }, // Overmind Without Shell
  {91, false, false, 0, false }, // Ultralisk Cavern
  {93, false, false, 0, false }, // Extractor
  {95, false, false, 0, false }, // Hydralisk Den
  {97, false, false, 0, false }, // Spire
  {99, false, false, 0, false }, // Spore Colony
  {101, false, false, 0, false }, // Infested Command Center Overlay
  {102, false, false, 0, false }, // Zerg Construction (Large)
  //{103, false, false }, // Zerg Building Morph
  //{104, false, false }, // Zerg Construction (Medium)
  //{105, false, false }, // Zerg Construction (Small)
  {107, false, false }, // Zerg Building Spawn (Small)
  {108, false, false }, // Zerg Building Spawn (Medium)
  {109, false, false }, // Zerg Building Spawn (Large)
  {110, false, false }, // Zerg Building Rubble (Small)
  {111, false, false }, // Zerg Building Rubble (Large)
  {112, false, false, 1 }, // Carrier
  {114, true, false, 1 }, // Carrier Engines
  {116, false, false, 2 }, // Interceptor
  {118, false, false, 1 }, // Shuttle
  {120, true, false, 2 }, // Shuttle Engines
  {122, false, false, 24 }, // Dragoon
  {124, false, false, 0, false }, // Dragoon Remnants
  {126, false, false, 17 }, // High Templar
  {129, false, false, 18 }, // Dark Templar (Hero)
  {130, false, false, 2 }, // Arbiter
  {132, true, false, 4 }, // Arbiter Engines
  {134, true, false }, // Archon Energy
  {135, true, false, 10 }, // Archon Being
  {136, true, false, 0, false }, // Archon Swirl
  {137, false, false, 1 }, // Probe
  {140, false, false, 2 }, // Scout
  {142, true, false, 2 }, // Scout Engines
  {144, false, false, 9 }, // Reaver
  {147, false, false, 1 }, // Scarab
  {148, false, false, 1 }, // Observer
  {151, false, false, 13 }, // Zealot
  //{153, false, false }, // Zealot Death
  {155, false, false, 0, false, true }, // Templar Archives
  {158, false, false, 0, false, true }, // Assimilator
  {161, false, false, 0, false, true }, // Observatory
  {164, false, false, 0, false, true }, // Citadel of Adun
  {167, false, false, 0, false, true }, // Forge
  {168, false, false }, // Forge Overlay
  {171, false, false, 0, false, true }, // Gateway
  {174, false, false, 0, false, true }, // Cybernetics Core
  {176, false, false }, // Cybernetics Core Overlay
  {178, false, false, 0, false }, // Khaydarin Crystal Formation
  {179, false, false, 0, false, true }, // Nexus
  {181, true, false }, // Nexus Overlay
  {183, false, false, 0, false, true }, // Photon Cannon
  {186, false, false, 0, false, true }, // Arbiter Tribunal
  {189, false, false, 0, false, true }, // Pylon
  {192, false, false, 0, false, true }, // Robotics Facility
  {195, false, false, 0, false, true }, // Shield Battery
  {196, true, false }, // Shield Battery Overlay
  {199, false, false, 0, false, true }, // Stargate
  {200, true, false }, // Stargate Overlay
  {203, false, false, 0, false }, // Stasis Cell/Prison
  {204, false, false, 0, false, true }, // Robotics Support Bay
  {207, false, false, 0, false }, // Protoss Temple
  {208, false, false, 0, false, true }, // Fleet Beacon
  {211, true, false }, // Warp Anchor
  {213, true, false }, // Explosion1 (Small)
  {214, true, false }, // Explosion1 (Medium)
  {215, true, false }, // Explosion (Large)
  {216, false, false }, // Protoss Building Rubble (Small)
  {217, false, false }, // Protoss Building Rubble (Large)
  {218, false, false, 1 }, // Battlecruiser
  {220, true, false, 2 }, // Battlecruiser Engines
  {221, false, false, 8 }, // Civilian
  {223, false, false, 1 }, // Dropship
  {225, true, false, 2 }, // Dropship Engines
  {226, false, false, 10 }, // Firebat
  {228, false, false, 13 }, // Ghost
  {230, false, false }, // Ghost Remnants
  //{231, false, false }, // Ghost Death
  //{232, true, false, true }, // Nuke Beam   (unused?)
  {233, true, false }, // Nuke Target Dot
  {234, false, false, 10 }, // Goliath Base
  {235, false, false, 11 }, // Goliath Turret
  {237, false, false, 13 }, // Sarah Kerrigan
  {239, false, false, 13 }, // Marine
  {241, false, false }, // Marine Remnants
  //{242, false, false }, // Marine Death
  {243, false, false, 1 }, // Wraith
  {245, true, false, 2 }, // Wraith Engines
  //{246, false, false }, // Scanner Sweep
  {247, false, false, 3 }, // SCV
  {249, true, false, 4 }, // SCV Glow
  {250, false, false, 3 }, // Siege Tank (Tank) Base
  {251, false, false, 1 }, // Siege Tank (Tank) Turret
  {253, false, false, 0, false }, // Siege Tank (Siege) Base
  {254, false, false, 1 }, // Siege Tank (Siege) Turret
  {256, false, false, 1 }, // Vulture
  {258, false, false, 0, false }, // Spider Mine
  {260, false, false, 0, false }, // Science Vessel (Base)
  {261, false, false, 1 }, // Science Vessel (Turret)
  //{262, false, true }, // Science Vessel Shadow
  {263, false, false, 0, false }, // Terran Academy
  {264, false, false }, // Academy Overlay
  {266, false, false, 0, false }, // Barracks
  {268, false, false, 0, false }, // Armory
  {269, false, false }, // Armory Overlay
  {271, false, false, 0, false }, // Comsat Station
  {272, false, false, 0, false }, // Comsat Station Connector
  {273, false, false }, // Comsat Station Overlay
  //{275, false, false }, // Command Center
  {276, false, false }, // Command Center Overlay
  {278, false, false, 0, false }, // Supply Depot
  {279, false, false }, // Supply Depot Overlay
  {281, false, false, 0, false }, // Control Tower
  {282, false, false, 0, false }, // Control Tower Connector
  {283, true, false }, // Control Tower Overlay
  {285, false, false, 0, false }, // Factory
  {286, true, false }, // Factory Overlay
  {288, false, false, 0, false }, // Covert Ops
  {289, false, false, 0, false }, // Covert Ops Connector
  {290, false, false }, // Covert Ops Overlay
  {292, false, false, 0, false }, // Ion Cannon
  {293, false, false, 0, false }, // Machine Shop
  {294, false, false, 0, false }, // Machine Shop Connector
  {296, false, false, 0, false }, // Missile Turret (Base)
  {297, false, false, 1, false }, // Missile Turret (Turret)
  {299, false, false, 0, false }, // Crashed Batlecruiser
  {301, false, false, 0, false }, // Physics Lab
  {302, false, false, 0, false }, // Physics Lab Connector
  {304, false, false, 0, false }, // Bunker
  {306, true, false, 1 }, // Bunker Overlay
  {307, false, false, 0, false }, // Refinery
  {309, false, false, 0, false }, // Science Facility
  {310, false, false }, // Science Facility Overlay
  {312, false, false, 0, false }, // Nuclear Silo
  {313, false, false, 0, false }, // Nuclear Silo Connector
  {314, false, false }, // Nuclear Silo Overlay
  {316, false, false, 1 }, // Nuclear Missile
  {318, true, false }, // Nuke Hit
  {319, false, false, 0, false }, // Starport
  {320, true, false }, // Starport Overlay
  {322, false, false, 0, false }, // Engineering Bay
  {323, false, false }, // Engineering Bay Overlay
  {325, false, false, 0, false }, // Terran Construction (Large)
  {327, false, false, 0, false }, // Terran Construction (Medium)
  {329, false, false, 0, false }, // Addon Construction
  //{330, false, false }, // Terran Construction (Small)
  {332, true, false }, // Explosion2 (Small)
  {333, true, false }, // Explosion2 (Medium)
  //{334, true, false }, // Building Explosion (Large)   // TODO: wtf?
  {335, false, false }, // Terran Building Rubble (Small)
  {336, false, false }, // Terran Building Rubble (Large)
  {337, true, false }, // Dark Swarm
  {338, false, false, 9 }, // Ragnasaur (Ash)
  {340, false, false, 11 }, // Rhynadon (Badlands)
  {342, false, false, 12 }, // Bengalaas (Jungle)
  {344, false, false, 0, true }, // Vespene Geyser
  {347, false, false, 0, true }, // Mineral Field Type1
  {349, false, false, 0, true }, // Mineral Field Type2
  {351, false, false, 0, true }, // Mineral Field Type3
  {354, false, false, 0, false }, // Zerg Beacon
  {355, true, false }, // Zerg Beacon Overlay
  {356, false, false, 0, false }, // Terran Beacon
  {357, true, false }, // Terran Beacon Overlay
  {358, false, false, 0, false }, // Protoss Beacon
  {359, true, false }, // Protoss Beacon Overlay
  {361, true, false }, // Lockdown Field (Small)
  {362, true, false }, // Lockdown Field (Medium)
  {363, true, false }, // Lockdown Field (Large)
  {364, true, false }, // Stasis Field Hit
  {365, true, false }, // Stasis Field (Small)
  //{366, true, false }, // Stasis Field (Medium)
  {367, true, false }, // Stasis Field (Large)
  {368, true, false }, // Recharge Shields (Small)
  //{369, true, false }, // Recharge Shields (Medium)
  {370, true, false }, // Recharge Shields (Large)
  {371, true, false }, // Defensive Matrix Front (Small)
  {372, true, false }, // Defensive Matrix Front (Medium)
  {373, true, false }, // Defensive Matrix Front (Large)
  {374, true, false }, // Defensive Matrix Back (Small)
  {375, true, false }, // Defensive Matrix Back (Medium)
  {376, true, false }, // Defensive Matrix Back (Large)
  {377, true, false }, // Defensive Matrix Hit (Small)
  {378, true, false }, // Defensive Matrix Hit (Medium)
  {379, true, false }, // Defensive Matrix Hit (Large)
  {380, true, false }, // Irradiate (Small)
  //{381, true, false }, // Irradiate (Medium)
  //{382, true, false }, // Irradiate (Large)
  {383, false, false }, // Ensnare Cloud
  {384, false, false }, // Ensnare Overlay (Small)
  {385, false, false }, // Ensnare Overlay (Medium)
  {386, false, false }, // Ensnare Overlay (Large)
  {387, false, false }, // Plague Cloud
  {388, false, false }, // Plague Overlay (Small)
  {389, false, false }, // Plague Overlay (Medium)
  {390, false, false }, // Plague Overlay (Large)
  {391, true, false }, // Recall Field
  {392, false, false, 0, false }, // Flag
  {393, false, false, 1 }, // Young Chrysalis
  {394, false, false, 0, false }, // Psi Emitter
  {395, false, false, 1 }, // Data Disc
  {396, false, false, 0, false }, // Khaydarin Crystal
  {397, false, false, 1 }, // Mineral Chunk Type1
  //{398, false, false, true }, // Mineral Chunk Type2
  {399, false, false, 2 }, // Protoss Gas Orb Type1
  //{400, false, false, true }, // Protoss Gas Orb Type2
  {401, false, false, 2 }, // Zerg Gas Sac Type1
  //{402, false, false, true }, // Zerg Gas Sac Type2
  {403, false, false, 0 }, // Terran Gas Tank Type1
  //{404, false, false }, // Terran Gas Tank Type2
  //{421, true, false, true }, // FlameThrower    // TODO: WTF?
  {422, true, false }, // Longbolt/Gemini Missiles Trail
  {423, false, false }, // Burrowing Dust
  {424, true, false, 4 }, // Shield Overlay
  {426, true, false }, // Double Explosion
  {427, true, false }, // Phase Disruptor Hit
  {428, true, false }, // Nuclear Missile Death
  {429, true, false }, // Spider Mine Death
  {430, true, false }, // Vespene Geyser Smoke1
  {431, true, false }, // Vespene Geyser Smoke2
  {432, true, false }, // Vespene Geyser Smoke3
  {433, true, false }, // Vespene Geyser Smoke4
  {434, true, false }, // Vespene Geyser Smoke5
  {435, true, false }, // Depleted Vespene Geyser Smoke1 Overlay
  {440, true, false }, // Fragmentation Grenade Hit
  {441, false, false }, // Grenade Shot Smoke
  //{442, false, false }, // Anti-Matter Missile Hit
  {443, true, false }, // Scarab/Anti-Matter Missile Overlay
  {444, true, false }, // Scarab Hit
  {445, true, false }, // Cursor Marker
  {446, true, false, 5 }, // Battlecruiser Attack Overlay
  {447, true, false }, // Burst Lasers Hit
  {449, true, false, 4 }, // High Templar Glow
  {450, true, false }, // Flames1 Type1 (Small)
  {451, true, false }, // Flames1 Type2 (Small)
  {452, true, false }, // Flames1 Type3 (Small)
  //{453, true, false }, // Flames2 Type3 (Small)
  //{454, true, false }, // Flames3 Type3 (Small)
  //{455, true, false }, // Flames4 Type3 (Small)
  //{456, true, false }, // Flames5 Type3 (Small)
  //{457, true, false }, // Flames6 Type3 (Small)
  {458, false, false, 0, false, false }, // Bleeding Variant1 Type1 (Small)
  {459, false, false, 0, false, false }, // Bleeding Variant1 Type2 (Small)
  {460, false, false, 0, false, false }, // Bleeding Variant1 Type3 (Small)
  {461, false, false, 0, false, false }, // Bleeding Variant1 Type4 (Small)
  {458, false, false, 0, false, false, true}, // Bleeding Variant2 Type1 (Small)
  {459, false, false, 0, false, false, true}, // Bleeding Variant2 Type2 (Small)
  {460, false, false, 0, false, false, true}, // Bleeding Variant2 Type3 (Small)
  {461, false, false, 0, false, false, true}, // Bleeding Variant2 Type4 (Small)
  {466, true, false }, // Flames2 Type1 (Small)
  {467, true, false }, // Flames2 Type2 (Small)
  {468, true, false }, // Flames7 Type3 (Small)
    /*
  {469, true, false }, // Flames3 Type1 (Small)
  {470, true, false }, // Flames3 Type2 (Small)
  {471, true, false }, // Flames8 Type3 (Small)
  {472, true, false }, // Flames1 Type1 (Large)
  {473, true, false }, // Flames1 Type2 (Large)
  {474, true, false }, // Flames1 Type3 (Large)
  {475, true, false }, // Flames2 Type3 (Large)
  {476, true, false }, // Flames3 Type3 (Large)
  {477, true, false }, // Flames4 Type3 (Large)
  {478, true, false }, // Flames5 Type3 (Large)
  {479, true, false }, // Flames6 Type3 (Large)
  {480, false, false }, // Bleeding Variant1 Type1 (Large)
  {481, false, false }, // Bleeding Variant1 Type2 (Large)
  {482, false, false }, // Bleeding Variant1 Type3 (Large)
  {483, false, false }, // Bleeding Variant1 Type4 (Large)
  {484, false, false }, // Bleeding Variant2 Type1 (Large)
  {485, false, false }, // Bleeding Variant2 Type3 (Large)
  {486, false, false }, // Bleeding Variant3 Type3 (Large)
  {487, false, false }, // Bleeding Variant2 Type4 (Large)
  {488, true, false }, // Flames2 Type1 (Large)
  {489, true, false }, // Flames2 Type2 (Large)
  {490, true, false }, // Flames7 Type3 (Large)
  {491, true, false }, // Flames3 Type1 (Large)
  {492, true, false }, // Flames3 Type2 (Large)
  {493, true, false }, // Flames8 Type3 (Large)
  */
  {494, false, false }, // Building Landing Dust Type1
  {495, false, false }, // Building Landing Dust Type2
  {496, false, false }, // Building Landing Dust Type3
  {497, false, false }, // Building Landing Dust Type4
  {498, false, false }, // Building Landing Dust Type5
  {499, false, false }, // Building Lifting Dust Type1
  {500, false, false }, // Building Lifting Dust Type2
  {501, false, false }, // Building Lifting Dust Type3
  {502, false, false }, // Building Lifting Dust Type4
  {503, false, false }, // White Circle
  {504, true, false }, // Needle Spine Hit
  {506, false, false }, // Sunken Colony Tentacle
  {509, true, false }, // Acid Spore
  {510, true, false }, // Acid Spore Hit
  {511, false, false }, // Glave Wurm
  {512, true, false }, // Glave Wurm/Seeker Spores Hit
  {513, true, false }, // Glave Wurm Trail
  {514, true, false }, // Seeker Spores Overlay
  {515, false, false }, // Seeker Spores
  {516, false, false }, // Queen Spell Holder
  {517, true, false }, // Consume
  {518, true, false, 6 }, // Guardian Attack Overlay
  //{519, true, false }, // Dual Photon Blasters Hit   // TODO: WTF?
  {520, true, false }, // Particle Beam Hit
  {521, false, false, 1 }, // Anti-Matter Missile
  {522, true, false, 1 }, // Pulse Cannon
  {523, true, false }, // Phase Disruptor
  {524, true, false }, // STA/STS Photon Cannon Overlay
  {525, true, false }, // Psionic Storm
  {526, true, false }, // Fusion Cutter Hit
  {527, true, false }, // Gauss Rifle Hit
  {528, false, false, 1 }, // Gemini Missiles
  {529, false, false, 1 }, // Lockdown/LongBolt/Hellfire Missile
  {530, true, false }, // Gemini Missiles Explosion
  //{531, true, false }, // C-10 Canister Rifle Hit
  {532, false, false }, // Fragmentation Grenade
  {533, true, false }, // Arclite Shock Cannon Hit
  {534, true, false, 1 }, // ATS/ATA Laser Battery
  {535, true, false, 1 }, // Burst Lasers
  {536, true, false, 1 }, // Siege Tank(Tank) Turret Attack Overlay
  {537, true, false, 7 }, // Siege Tank(Siege) Turret Attack Overlay
  {538, true, false }, // Science Vessel Overlay (Part1)
  {539, true, false }, // Science Vessel Overlay (Part2)
  {540, true, false }, // Science Vessel Overlay (Part3)
  {541, true, false, 4 }, // Yamato Gun
  //{542, true, false, true }, // Yamato Gun Trail
  {543, true, false }, // Yamato Gun Overlay
  {544, true, false }, // Yamato Gun Hit
  {545, true, false }, // Hallucination Hit
  {546, true, false }, // Scanner Sweep Hit
  //{548, true, false }, // Psionic Shockwave Hit
  {549, true, false, 4 }, // Archon Beam
//  {550, true, false }, // Psionic Storm Part1
//  {551, true, false }, // Psionic Storm Part2
//  {552, true, false }, // Psionic Storm Part3
//  {553, true, false }, // Psionic Storm Part4
  //{554, false, false, true }, // EMP Shockwave Missile
  {555, true, false }, // EMP Shockwave Hit (Part1)
  {556, true, false }, // EMP Shockwave Hit (Part2)
  //{557, true, false }, // Hallucination Death1   // TODO: WTF?
  //{558, true, false }, // Hallucination Death2
  //{559, true, false }, // Hallucination Death3
//  {589, false, false }, // 2/38 Ash
//  {591, false, false }, // 2/39 Ash
//  {593, false, false }, // 2/41 Ash
//  {595, false, false }, // 2/40 Ash
//  {597, false, false }, // 2/42 Ash
//  {599, false, false }, // 2/43 Ash
//  {600, false, false }, // 2/44 Ash
//  {601, false, false }, // 2/1 Ash
//  {602, false, false }, // 2/4 Ash
//  {603, false, false }, // 2/5 Ash
//  {604, false, false }, // 2/30 Ash
//  {605, false, false }, // 2/28 Ash
//  {606, false, false }, // 2/29 Ash
//  {607, false, false }, // 4/1 Ash
//  {608, false, false }, // 4/2 Ash
//  {609, false, false }, // 4/3 Ash
//  {610, false, false }, // 4/56 Jungle
//  {612, false, false }, // 4/57 Jungle
//  {614, false, false }, // 4/58 Jungle
//  {616, false, false }, // 4/59 Jungle
//  {618, false, false }, // 9/5 Jungle
//  {620, false, false }, // 9/6 Jungle
//  {622, false, false }, // 9/7 Jungle
//  {624, false, false }, // 4/51 Jungle
//  {626, false, false }, // 4/52 Jungle
//  {628, false, false }, // 4/54 Jungle
//  {630, false, false }, // 4/53 Jungle
//  {632, false, false }, // 9/1 Jungle
//  {634, false, false }, // 9/2 Jungle
//  {636, false, false }, // 9/3 Jungle
//  {638, false, false }, // 9/4 Jungle
//  {640, false, false }, // 4/12 Jungle
//  {641, false, false }, // 4/13 Jungle
//  {642, false, false }, // 4/1 Jungle
//  {643, false, false }, // 4/3 Jungle
//  {644, false, false }, // 4/2 Jungle
//  {645, false, false }, // 4/5 Jungle
//  {646, false, false }, // 4/4 Jungle
//  {647, false, false }, // 4/9 Jungle
//  {648, false, false }, // 4/10 Jungle
//  {649, false, false }, // 5/5 Jungle
//  {650, false, false }, // 5/7 Jungle
//  {651, false, false }, // 5/6 Jungle
//  {652, false, false }, // 5/9 Jungle
//  {653, false, false }, // 5/8 Jungle
//  {654, false, false }, // 4/6 Jungle
//  {655, false, false }, // 4/7 Jungle
//  {656, false, false }, // 4/17 Jungle
//  {657, false, false }, // 13/4 Jungle
//  {658, false, false }, // 11/5 Jungle
//  {659, false, false }, // 11/6 Jungle
//  {660, false, false }, // 11/7 Jungle
//  {661, false, false }, // 11/8 Jungle
//  {662, false, false }, // 11/10 Jungle
//  {663, false, false }, // 11/11 Jungle
//  {664, false, false }, // 11/12 Jungle
//  {665, false, false }, // 7/4 Platform
//  {667, false, false }, // 7/5 Platform
//  {669, false, false }, // 7/6 Platform
//  {671, false, false }, // 7/1 Platform
//  {673, false, false }, // 7/2 Platform
//  {675, false, false }, // 7/3 Platform
//  {677, false, false }, // 7/9 Platform
//  {678, false, false }, // 7/10 Platform
//  {679, false, false }, // 7/8 Platform
//  {680, false, false }, // 7/7 Platform
//  {681, false, false }, // 7/26 Platform
//  {682, false, false }, // 7/24 Platform
//  {683, false, false }, // 7/28 Platform
//  {684, false, false }, // 7/27 Platform
//  {685, false, false }, // 7/25 Platform
//  {686, false, false }, // 7/29 Platform
//  {687, false, false }, // 7/30 Platform
//  {688, false, false }, // 7/31 Platform
//  {689, false, false }, // 12/1 Platform
//  {690, false, false }, // 9/27 Platform
//  {691, false, false }, // 5/54 Badlands
//  {693, false, false }, // 5/55 Badlands
//  {695, false, false }, // 5/56 Badlands
//  {697, false, false }, // 5/57 Badlands
//  {699, false, false }, // 6/16 Badlands
//  {700, false, false }, // 6/17 Badlands
//  {701, false, false }, // 6/20 Badlands
//  {702, false, false }, // 6/21 Badlands
//  {703, false, false }, // 5/10 Badlands
//  {704, false, false }, // 5/50 Badlands
//  {706, false, false }, // 5/52 Badlands
//  {708, false, false }, // 5/53 Badlands
//  {710, false, false }, // 5/51 Badlands
//  {712, false, false }, // 6/3 Badlands
//  {713, false, false }, // 11/3 Badlands
//  {714, false, false }, // 11/8 Badlands
//  {715, false, false }, // 11/6 Badlands
//  {716, false, false }, // 11/7 Badlands
//  {717, false, false }, // 11/9 Badlands
//  {718, false, false }, // 11/10 Badlands
//  {719, false, false }, // 11/11 Badlands
//  {720, false, false }, // 11/12 Badlands
//  {721, false, false }, // 11/13 Badlands
//  {722, false, false }, // 11/14 Badlands
//  {723, false, false }, // 1/13 Badlands
//  {724, false, false }, // 1/9 Badlands
//  {725, false, false }, // 1/11 Badlands
//  {726, false, false }, // 1/14 Badlands
//  {727, false, false }, // 1/10 Badlands
//  {728, false, false }, // 1/12 Badlands
//  {729, false, false }, // 1/15 Badlands
//  {730, false, false }, // 1/7 Badlands
//  {731, false, false }, // 1/5 Badlands
//  {732, false, false }, // 1/16 Badlands
//  {733, false, false }, // 1/8 Badlands
//  {734, false, false }, // 1/6 Badlands
  {735, false, false, 0, false }, // Floor Gun Trap
  {736, false, false, 0, false }, // Floor Missile Trap
  {737, false, false, 1 }, // Floor Missile Trap Turret
  {738, false, false }, // Wall Missile Trap
  //{739, false, false }, // Wall Missile Trap2
  {740, false, false }, // Wall Flame Trap
  //{741, false, false }, // Wall Flame Trap2
  {742, false, false, 0, false }, // Left Upper Level Door
  //{743, false, false }, // Right Upper Level Door
  //{744, false, false }, // 4/15 Installation1
  //{745, false, false }, // 4/15 Installation2
  //{746, false, false }, // 3/9 Installation
  //{747, false, false }, // 3/10 Installation
  //{748, false, false }, // 3/11 Installation
  //{749, false, false }, // 3/12 Installation
  {750, false, false, 0, false }, // Substructure Left Door
  //{751, false, false }, // Substructure Right Door
  //{752, false, false }, // 3/1 Installation
  //{753, false, false }, // 3/2 Installation
  {754, false, false }, // Substructure Opening Hole
 // {755, false, false }, // 7/21 Twilight
 // {756, false, false }, // Unknown Twilight
 // {757, false, false }, // 7/13 Twilight
 // {758, false, false }, // 7/14 Twilight
 // {759, false, false }, // 7/16 Twilight
 // {760, false, false }, // 7/15 Twilight
 // {761, false, false }, // 7/19 Twilight
 // {762, false, false }, // 7/20 Twilight
 // {763, false, false }, // 7/17 Twilight
 // {764, false, false }, // 6/1 Twilight
 // {765, false, false }, // 6/2 Twilight
 // {766, false, false }, // 6/3 Twilight
 // {767, false, false }, // 6/4 Twilight
 // {768, false, false }, // 6/5 Twilight
 // {769, false, false }, // 8/3 Twilight1
 // {770, false, false }, // 8/3 Twilight2
 // {771, false, false }, // 9/29 Ice
 // {773, false, false }, // 9/28 Ice
 // {775, false, false }, // 12/38 Ice
 // {777, false, false }, // 12/37 Ice
 // {779, false, false }, // 12/33 Ice1
 // {781, false, false }, // 9/21 Ice
 // {783, false, false }, // 9/15 Ice
 // {785, false, false }, // 9/16 Ice
 // {787, false, false }, // Unknown787
 // {788, false, false }, // Unknown788
 // {789, false, false }, // 12/9 Ice1
 // {790, false, false }, // 12/10 Ice1
 // {791, false, false }, // 9/24 Ice
 // {793, false, false }, // 9/23 Ice
 // {795, false, false }, // Unknown795
 // {797, false, false }, // 12/7 Ice
 // {799, false, false }, // 12/8 Ice
 // {801, false, false }, // 12/9 Ice2
 // {803, false, false }, // 12/10 Ice2
 // {805, false, false }, // 12/40 Ice
 // {807, false, false }, // 12/41 Ice
 // {809, false, false }, // 12/42 Ice
 // {811, false, false }, // 12/5 Ice
 // {813, false, false }, // 12/6 Ice
 // {815, false, false }, // 12/36 Ice
 // {817, false, false }, // 12/32 Ice
 // {819, false, false }, // 12/33 Ice2
 // {821, false, false }, // 12/34 Ice
 // {823, false, false }, // 12/24 Ice1
 // {825, false, false }, // 12/25 Ice1
 // {827, false, false }, // 12/30 Ice1
 // {829, false, false }, // 12/31 Ice
 // {831, false, false }, // 12/20 Ice
 // {832, false, false }, // 12/30 Ice2
 // {834, false, false }, // 9/22 Ice
 // {836, false, false }, // 12/24 Ice2
 // {838, false, false }, // 12/25 Ice2
 // {840, false, false }, // Unknown840
 // {841, false, false }, // 4/1 Ice
 // {842, false, false }, // 6/1 Ice
 // {843, false, false }, // 5/6 Ice
 // {845, false, false }, // 5/7 Ice
 // {847, false, false }, // 5/8 Ice
 // {849, false, false }, // 5/9 Ice
 // {851, false, false }, // 10/10 Desert1
 // {852, false, false }, // 10/12 Desert1
 // {854, false, false }, // 10/8 Desert1
 // {856, false, false }, // 10/9 Desert1
 // {858, false, false }, // 6/10 Desert
 // {860, false, false }, // 6/13 Desert1
 // {862, false, false }, // Unknown Desert
 // {864, false, false }, // 10/12 Desert2
 // {866, false, false }, // 10/9 Desert2
 // {868, false, false }, // 10/10 Desert2
 // {870, false, false }, // 10/11 Desert
 // {872, false, false }, // 10/14 Desert
 // {874, false, false }, // 10/41 Desert
 // {876, false, false }, // 10/39 Desert
 // {878, false, false }, // 10/8 Desert2
 // {880, false, false }, // 10/6 Desert
 // {881, false, false }, // 10/7 Desert
 // {883, false, false }, // 4/6 Desert
 // {885, false, false }, // 4/11 Desert
 // {887, false, false }, // 4/10 Desert
 // {889, false, false }, // 4/9 Desert
 // {890, false, false }, // 4/7 Desert
 // {892, false, false }, // 4/12 Desert
 // {894, false, false }, // 4/8 Desert
 // {895, false, false }, // 4/13 Desert
 // {897, false, false }, // 4/17 Desert
 // {898, false, false }, // 4/15 Desert1
 // {900, false, false }, // 10/23 Desert
 // {902, false, false }, // 10/5 Desert
 // {904, false, false }, // 6/13 Desert2
 // {906, false, false }, // 6/20 Desert
 // {907, false, false }, // 4/15 Desert2
 // {909, false, false }, // 8/23 Desert
 // {911, false, false }, // 12/1 Desert Overlay
 // {912, false, false }, // 11/3 Desert
  {914, false, false, 0, false }, // Lurker Egg
  {915, false, false, 10 }, // Devourer
  {917, false, false }, // Devourer Birth
  {918, false, false }, // Devourer Death
  {919, false, false }, // Lurker Birth
  {920, false, false, 7 }, // Lurker + Lurker Remnants
  //{921, false, false, true }, // Lurker
  {923, false, false, 0, false }, // Overmind Cocoon
  {925, true, false }, // Dark Archon Energy
  {926, true, false, 10 }, // Dark Archon Being
  {927, true, false }, // Dark Archon Swirl
  {928, true, false }, // Dark Archon Death
  {929, false, false, 5 }, // Corsair
  {931, true, false, 2 }, // Corsair Engines
  //{933, false, false, true }, // Dark Templar (Unit)
  {934, false, false, 0, false }, // Warp Gate
  {936, true, false }, // Warp Gate Overlay
  {937, false, false, 0, false }, // Xel'Naga Temple
  {939, false, false, 1 }, // Valkyrie
  {941, true, false, 2 }, // Valkyrie Engines
  {944, false, false, 13 }, // Medic
  {946, false, false }, // Medic Remnants
  {947, false, false, 0, false }, // Psi Disrupter
  {949, false, false, 0, false }, // Power Generator
  {951, true, false }, // Disruption Web
  {952, false, false, 12 }, // Scantid (Desert)
  {954, false, false, 12 }, // Kakaru (Twilight)
  {956, false, false, 8 }, // Ursadon (Ice)
  {958, false, false, 0, false }, // Uraj
  {959, false, false, 0, false }, // Khalis
  {960, true, false }, // Halo Rockets Trail
  {961, false, false }, // Subterranean Spines
  {962, false, false, 4 }, // Corrosive Acid Shot
  {963, false, false }, // Corrosive Acid Hit
  //{964, true, false }, // Neutron Flare  // TODO: WTF?
  {965, false, false, 1 }, // Halo Rockets
  //{966, false, false }, // Optical Flare Grenade
  {967, true, false }, // Restoration Hit (Small)
  //{968, true, false }, // Restoration Hit (Medium)
  {969, true, false }, // Restoration Hit (Large)
  {973, true, false }, // Mind Control Hit (Small)
  {974, true, false }, // Mind Control Hit (Medium)
  {975, true, false }, // Mind Control Hit (Large)
  {976, true, false }, // Optical Flare Hit (Small)
  //{977, true, false }, // Optical Flare Hit (Medium) // TODO: WTF?
  {978, true, false }, // Optical Flare Hit (Large)
  {979, true, false }, // Feedback (Small)
  {980, true, false }, // Feedback (Medium)
  {981, true, false }, // Feedback Hit (Large)
  {982, true, false }, // Maelstorm Overlay (Small)
  {983, true, false }, // Maelstorm Overlay (Medium)
  {984, true, false }, // Maelstorm Overlay (Large)
  {986, false, false }, // Acid Spores (1-9) Overlay (Small)
  {990, false, false }, // Acid Spores (1-9) Overlay (Medium)
  {994, false, false }, // Acid Spores (1-9) Overlay (Large)
  {998, true, false } // Maelstrom Hit
};

