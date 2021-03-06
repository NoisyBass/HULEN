Map_GO = {

	Player_GO = {
		type = "GameObject",
		blueprint = "Player_GO",
		isPlayer = true,
		state = "Body",
		playerDeathTime = 3,
		playerCanDie = false,
		kasai = "Kasai_GO",
		charge = "Charge_Prefab",
		pickObjectAnimation = "pick_object",

		-- Life Bar
		billboard_position = {-25,16,0},
		billboard_color    = {1,1,1},
		billboard_width    = 10,
		billboard_height   = 1,
		billboard_material = "LifeBar",
	},

	--[[Crawler_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},]]

	Lightbulb_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	--[[Centaur_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},]]

	Kasai_GO = {
		type = "GameObject",
		blueprint = "Empty",
		isLight = true,
		state = "Body",
	},

	Camera_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	World0_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World1_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World2_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World3_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	World4_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body"
	},

	Platform1_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Both",
	},

	Platform2_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	Platform3_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Both",
	},

	Platform4_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	Platform5_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Both",
	},

	Platform6_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Both",
	},

	Platform7_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Shadow",
	},

	Platform8_GO = {
		type = "GameObject",
		prefab = "World_Prefab",
	},

	Spike_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Shadow",
	},

	Lever_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	LeverTarget_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	FinishLevel_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	--[[LightLever_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},]]

	LightLeverTarget_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	LightLeverEnd_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	LightLeverEndTarget_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	--[[Cosa_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},]]--
}

Map = {

	FinishLevel_Body = {
		type = "Body",
		blueprint = "FinishLevel",
		game_object = "FinishLevel_GO",
		position = {27, -8, 0},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		physic_dimensions = { 1,1,1 },
	},

	LeverTarget_Body = {
		type = "Body",
		blueprint = "LeverTarget",
		game_object = "LeverTarget_GO",
		position = {2, -12, 0},
		scale = {1, 5, 1},
		model = "Cube.mesh",
		position2 = {2, -7, 0},
		speed = 10,
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_mass = 1,
		physic_shape = "box",
		physic_dimensions = { 1,3,2},
	},

	LightLeverTarget_Body = {
		type = "Body",
		blueprint = "LeverTarget",
		game_object = "LightLeverTarget_GO",
		position = {4, -12, 0},
		scale = {1, 5, 1},
		model = "Cube.mesh",
		position2 = {4, -7, 0},
		speed = 10,
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_mass = 1,
		physic_shape = "box",
		physic_dimensions = { 1,3,2},
	},

	LightLeverEndTarget_Body = {
		type = "Body",
		blueprint = "LeverTarget",
		game_object = "LightLeverEndTarget_GO",
		position = {6, -12, 0},
		scale = {1, 5, 1},
		model = "Cube.mesh",
		position2 = {6, -7, 0},
		speed = 10,
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_mass = 1,
		physic_shape = "box",
		physic_dimensions = { 1,3,2},
	},

	Lever_Body = {
		type = "Body",
		blueprint = "Lever",
		game_object = "Lever_GO",
		position = {0, -14, -0.5},
		model = "Lever.mesh",
		interactuable_area_radius = 3,
		player = "Player_GO",
		lever_GO_target  = "LeverTarget_GO",

		--Sound
		switchOnVolume = 0.1,
		switchOnPitch = 1,

		switchOffVolume = 0.5,
		switchOffPitch = 1,
	},

	--[[LightLever_Body = {
		type = "Body",
		blueprint = "LightLever",
		game_object = "LightLever_GO",
		light_lever_GO_target = "LightLeverTarget_GO",
		position = {-8, -3.5, -2},
		model = "LightSwitch.mesh",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/LightSwitch.RepX",
		physic_change_coords = true,
	},]]


	LightLeverEnd_Body = {
		type = "Body",
		blueprint = "LightLever",
		game_object = "LightLeverEnd_GO",
		light_lever_GO_target = "LightLeverEndTarget_GO",
		position = {10, -3.5, -1},
		model = "EndLevelLightSwitch.mesh",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/EndLevelLightSwitch.RepX",
		physic_change_coords = true,
	},
	
	Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, 0, 0.1},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Player",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		defaultVision = 5,

		-- Sounds
		walkSound = "PrisonerWalk",
		walkVolume = 0.8,
		walkPitch = 1.65,

		jumpSound = "PrisonerJump",
		jumpVolume = 0.3, 
		jumpPitch = 1,

		landSound = "PrisonerLand",
		landVolume = 0.3,
		landPitch = 1,

		-- Avatar controller
		speed = 10,
		jump_speed = 20,
		jump_height = 8,
		gravity = 8,
		

		--Animations
		defaultAnimation = "idle_cycle_1",
		defaultAnimationVelocity = 5,
		idle1Animation = { "idle_cycle_1", 1, "null"},
		idle2Animation = { "idle_cycle_2", 1, "null"},
		walkAnimation  = { "Walking_cycle", 1, "null"},
		runAnimation   = { "Running_cycle", 1, "null"},
		deathAnimation = { "death", 1, "null"},
		delayinitJump  = 0.3,
		jump1Animation = { "Jump_movement", 2, "null"},
		fall1Animation = { "fall", 2, "null"},
		land1Animation = { "landing", 4.5 , "null"},
		--jump2Animation = { "", 2, "null"},
		--fall2Animation = { "", 2, "null"},
		--land2Animation = { "", 2, "null"},
		pickObjectAnimation = { "pick_object",1, "null"},

		--Blending
		defaultBlendingVelocity = 5,
		idle1Blending = { "idle_cycle_1", 2, "null"},
		idle2Blending = { "idle_cycle_2", 2, "null"},
		walkBlending  = { "Walking_cycle", 5, "null"},
		runBlending   = { "Running_cycle", 2, "null"},
		deathBlending = { "death", 2, "null"},
		jump1Blending = { "Jump_movement", 2, "null"},
		fall1Blending = { "fall", 2, "null"},
		land1Blending = { "landing", 2, "null"},
		--jump2Blending = { "", 2, "null"},
		--fall2Blending = { "", 2, "null"},
		--land2Blending = { "", 2, "null"},
		pickObjectBlending = { "pick_object", 2, "null"},
	},

	Player_Shadow = {
		type = "Shadow",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, 0, -3.5},
		scale = {4, 4, 4},
		--model = "marine.mesh",
		model = "Main_character.mesh",
		material = "Black",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,

		-- Avatar controller
		speed = 10,
		jump_speed = 20,
		jump_height = 8,
		gravity = 8,

		-- Sounds
		walkSound = "PrisonerShadowWalk",
		walkVolume = 0.8,
		walkPitch = 1.65,

		jumpSound = "PrisonerShadowJump",
		jumpVolume = 0.3, 
		jumpPitch = 1,

		landSound = "PrisonerShadowLand",
		landVolume = 0.3,
		landPitch = 1,

		--Animations
		defaultAnimation = "idle_cycle_1",
		defaultAnimationVelocity = 5,
		idle1Animation = { "idle_cycle_1", 1, "null"},
		idle2Animation = { "idle_cycle_2", 1, "null"},
		walkAnimation  = { "Walking_cycle", 1, "null"},
		runAnimation   = { "Running_cycle", 1, "null"},
		deathAnimation = { "death", 1, "null"},
		delayinitJump  = 0.3,
		jump1Animation = { "Jump_movement", 2, "null"},
		fall1Animation = { "fall", 2, "null"},
		land1Animation = { "landing", 4.5 , "null"},
		--jump2Animation = { "", 2, "null"},
		--fall2Animation = { "", 2, "null"},
		--land2Animation = { "", 2, "null"},
		pickObjectAnimation = { "pick_object",1, "null"},

		--Blending
		defaultBlendingVelocity = 5,
		idle1Blending = { "idle_cycle_1", 2, "null"},
		idle2Blending = { "idle_cycle_2", 2, "null"},
		walkBlending  = { "Walking_cycle", 5, "null"},
		runBlending   = { "Running_cycle", 2, "null"},
		deathBlending = { "death", 2, "null"},
		jump1Blending = { "Jump_movement", 2, "null"},
		fall1Blending = { "fall", 2, "null"},
		land1Blending = { "landing", 2, "null"},
		--jump2Blending = { "", 2, "null"},
		--fall2Blending = { "", 2, "null"},
		--land2Blending = { "", 2, "null"},
		pickObjectBlending = { "pick_object", 2, "null"},
	},

	--[[Crawler_Body = {
		type = "Body",
		blueprint = "Crawler",
		game_object = "Crawler_GO",
		position = {-11, 0, 0},
		scale = {0.2, 0.2, 0.2},
		model = "marine.mesh",
		material = "Red",
		defaultAnimation = "Idle",
		walkRightAnimation = "WalkBack",
		idleAnimation = "Idle",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 0.1,
		gravity = 15,
		guizmo = false,
		guizmoSize = 10,
		speed = 5,
		patrolPosition1 = {0, 0, 0},
		patrolPosition2 = {5, 0, 0},
		fsm_initial_state = "Crawler_Patrol",
	},]]

	Lightbulb_Body = {
		type = "Body",
		blueprint = "Lightbulb",
		game_object = "Lightbulb_GO",
		rollRotate = 90,
		position = {3, 0, 0},
		direction = "left",
		scale = {0.2, 0.2, 0.2},
		model = "LightBulb.mesh",
		material = "Red",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 0.1,
		gravity = 15,
		guizmo = false,
		guizmoSize = 10,
		speed = 2.5,
		--patrolPosition1 = {4, -14, 0},
		--patrolPosition2 = {10, -14, 0},
		patrolPosition1 = {0, 0, 0},
		patrolPosition2 = {5, 0, 0},
		positionToGo = {0,0,0},
		fsm_initial_state = "Lightbulb_Patrol",
		defaultVision = 10,

		--Animations
		defaultAnimation = "walking_cycle",
		defaultAnimationVelocity = 1,
		idle1Animation =           {"idle_search", 1, "null"},
		walkAnimation =            {"walking_cycle", 1, "null"},
		runAnimation =             {"running_cycle", 1, "null"},
		changeDirectionAnimation = {"change_direction", 1, "null"},
		eatLightAnimation        = {"eat_light",1, "null"},
		attackAnimation          = {"attack", 1, "null"},
		
		--Blending
		defaultBlendingVelocity = 5,
		idle1Blending =           {"idle_search", 2, "null"},
		walkBlending =            {"walking_cycle", 2, "null"},
		runBlending =             {"running_cycle", 2, "null"},
		changeDirectionBlending = {"change_direction", 2, "null"},
		eatLightBlending        = {"eat_light",2, "null"},
		attackBlending          = {"attack", 2, "null"},
	},

	--[[Centaur_Body = {
		type = "Body",
		blueprint = "Centaur",
		game_object = "Centaur_GO",
		position = {3, -3.9, 0},
		direction = "left",
		--model = "marine.mesh",
		--material = "Red",
		--defaultAnimation = "Idle",
		--walkRightAnimation = "WalkBack",
		--idleAnimation = "Idle",

		model = "Centaur_animations_v2.mesh",
		material = "blinn1",
		defaultAnimation = "idle",
		walkRightAnimation = "walking_cycle",
		idleAnimation = "idle",

		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 0.1,
		gravity = 15,
		guizmo = false,
		guizmoSize = 10,
		speed = 12,
		defaultVision = 10,
		fsm_initial_state = "Centaur_Idle",

		--Animations
		defaultAnimation = "idle",
		defaultAnimationVelocity = 1,
		idle1Animation =           {"idle", 1, "null"},
		walkAnimation =            {"walking_cycle", 1, "null"},
		runAnimation =             {"running_cycle", 1, "null"},
		changeDirectionAnimation = {"change_direction", 1, "null"},
		startRunAnimation =        {"start_run", 1, "null"},
		preparationAnimation =     {"preparation", 1, "null"},
		killScreamAnimation =      {"kill_scream", 1, "null"},
		deathAnimation =           {"crash_death", 1, "null"},

		--Blending
		defaultBlendingVelocity = 5,
		idle1Blending =           {"idle", 2, "null"},
		walkBlending =            {"walking_cycle", 2, "null"},
		runBlending =             {"running_cycle", 2, "null"},
		changeDirectionBlending = {"change_direction", 2, "null"},
		startRunBlending =        {"start_run", 2, "null"},
		preparationBlending =     {"preparation", 2, "null"},
		killScreamBlending =      {"kill_scream", 2, "null"},
		deathBlending =           {"crash_death", 2, "null"},
	},]]

	Kasai = {
		type = "Body",
		blueprint = "Kasai",
		game_object = "Kasai_GO",
		position = {0,0,0},
		light_position = {0,0,0},
		specular_colour = {1,1,1},
		diffuse_colour = {1,1,1},
		model = "Sphere.mesh",
		scale = {0.75, 0.75, 0.75},
		material = "Charge_on",
		--flare_material = "Flare",
		--flare_colour = {1,1,1},
		--flare_size = 10,
		light_attenuation_range = 6.5,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		player = "Player_GO",
		lighting_area_radius = 6.5,

		-- Graphic Charge
		graphicChargeVelocity = 5.5,
		thrownChargeVelocity = 10,
		graphicChargeRadius = 3,
		graphicChargeRotationBar = 0.2,
		graphicChargesDeltaSeparation = 0.15,
		graphicChargesDeltaSeparationToFirstCharge = 0.85,

		-- Ribbon Trail
		ribbonTrail_material          = "LightRibbonTrail",
		ribbonTrail_lenght            = 500,
		ribbonTrail_maxChainElements  = 500,
		ribbonTrail_initialRGBColor   = {1.0,1.0,1.0},
		ribbonTrail_initialAlphaColor = 1,
		ribbonTrail_ChangeRGBColor    = {0.5,0.5,0.5},
		ribbonTrail_ChangelAlphaColor = 0.5,
		ribbonTrail_initialWidth      = 1,
		ribbonTrail_fadedTime         = 0.4,
	},

	Camera = {
		type = "Body",
		blueprint = "Camera",
		game_object = "Camera_GO",
		position = {0, 0, 30},
		fixed = true,
		ratio = 169,
		fov = 60,
	},

	World0 = {
		type = "Body",
		blueprint = "Wall",
		game_object = "World0_GO",
		position = {30, 0, 0},
		scale = {1, 35, 10},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		material = "White",
		physic_dimensions = { 1, 35, 10 },
	},
		

	World1 = {
		type = "Body",
		blueprint = "DeathPlane",
		game_object = "World1_GO",
		position = {0, -25, 0},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_trigger = true,
		physic_shape = "box",
		scale = {60, 1, 10},
		physic_dimensions = { 65, 1, 10 },
	},

	World2 = {
		type = "Body",
		blueprint = "Wall",
		game_object = "World2_GO",
		position = {0, 17, 0},
		scale = {60, 1, 10},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		material = "White",
		physic_dimensions = { 65, 1, 10 },
	},

	World3 = {
		type = "Body",
		blueprint = "Wall",
		game_object = "World3_GO",
		position = {-30, 0, 0},
		scale = {1, 35, 10},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "static",
		physic_shape = "box",
		material = "White",
		physic_dimensions = { 1, 35, 10 },
	},

	World4 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World4_GO",
		position = {0, 0, -3.5},
		-- Graphic Entity
		--model = "Plane.mesh",
		graphic_file = false,
		graphic_type = "plane",
		graphic_up_vector = {0, 0, 1},
		graphic_parallel_vector = {0, 1, 0},
		graphic_width = 65,
		graphic_height = 50,
		material = "perPixel",
	},

	Platform1_Body = {
		type = "Body",
		game_object = "Platform1_GO",
		prefab = "World_Prefab",
		position = {-25, -4, 0},
		scale = {10, 1, 3.5},
		physic_dimensions = { 10, 1, 3.5 },
	},

	Platform1_Shadow = {
		type = "Shadow",
		game_object = "Platform1_GO",
		prefab = "World_Prefab",
		position = {-25, -4, -3.5},
		scale = {10, 1, 0.1},
		physic_dimensions = { 10, 1, 0.1 },
	},

	Platform2 = {
		type = "Body",
		game_object = "Platform2_GO",
		prefab = "World_Prefab",
		position = {-15, -4, 0},
		scale = {10, 1, 1},
		physic_dimensions = { 10, 1, 1 },
	},

	Platform3_Body = {
		type = "Body",
		game_object = "Platform3_GO",
		prefab = "World_Prefab",
		position = {2, -4, 0},
		scale = {25, 1, 3.5},
		physic_dimensions = { 25, 1, 3.5 },
	},

	Platform3_Shadow = {
		type = "Shadow",
		game_object = "Platform3_GO",
		prefab = "World_Prefab",
		position = {2, -4, -3.5},
		scale = {25, 1, 0.1},
		physic_dimensions = { 25, 1, 0.1 },
	},

	Platform4 = {
		type = "Body",
		game_object = "Platform4_GO",
		prefab = "World_Prefab",
		position = {-15, -12, 0},
		scale = {10, 1, 3.5},
		physic_dimensions = { 10, 1, 3.5 },
	},

	Platform5_Body = {
		type = "Body",
		game_object = "Platform5_GO",
		prefab = "World_Prefab",
		position = {15, 6, 0},
		scale = {1, 21, 3.5},
		physic_dimensions = { 1, 21, 3.5 },
	},

	Platform5_Shadow = {
		type = "Shadow",
		game_object = "Platform5_GO",
		prefab = "World_Prefab",
		position = {15, 6, -3.5},
		scale = {1, 21, 0.1},
		physic_dimensions = { 1, 21, 0.1 },
	},

	Platform6_Body = {
		type = "Body",
		game_object = "Platform6_GO",
		prefab = "World_Prefab",
		position = {5, -15, 0},
		scale = {20, 1, 3.5},
		physic_dimensions = { 20, 1, 3.5 },
	},

	Platform6_Shadow = {
		type = "Shadow",
		game_object = "Platform6_GO",
		prefab = "World_Prefab",
		position = {5, -15, -3.5},
		scale = {20, 1, 0.1},
		physic_dimensions = { 20, 1, 0.1 },
	},

	Platform7_Shadow = {
		type = "Shadow",
		game_object = "Platform7_GO",
		prefab = "World_Prefab",
		position = {20, -12, -3.5},
		scale = {8, 1, 0.1},
		physic_dimensions = { 8, 1, 0.1 },
	},

	Platform8_Body = {
		type = "Body",
		game_object = "Platform8_GO",
		prefab = "World_Prefab",
		position = {25, -9, 0},
		scale = {6, 1, 3.5},
		physic_dimensions = { 5, 1, 3.5 },
	},

	Spike_Shadow = {
		type = "Shadow",
		game_object = "Spike_GO",
		prefab = "Spike_Prefab",
		position = {0,-14, -3.5},
		scale = {1, 1, 0.1},
	},

	--[[Cosa_Body = {
		type = "Body",
		game_object = "Cosa_GO",
		prefab = "Spike_Prefab",
		model = "Test_Main_character.mesh",
		position = {0,-14, 0},
		scale = {1, 1, 0.1},
		guizmo = false,
		guizmoSize = 10,
	},]]--

}