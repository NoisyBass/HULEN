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
	},

	Crawler_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	Lightbulb_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

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
		position = {-15, -3, 0},
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
		position = {-20, 5, 0},
		model = "Cube.mesh",
		position2 = {-20, 10, 0},
		speed = 0.01,
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_mass = 1,
		physic_shape = "box",
		physic_dimensions = { 1,1,1 },
	},

	Lever_Body = {
		type = "Body",
		blueprint = "Lever",
		game_object = "Lever_GO",
		position = {-20, -3, 0},
		model = "Cube.mesh",
		interactuable_area_radius = 3,
		player = "Player_GO",
		lever_GO_target  = "LeverTarget_GO",
	},
	
	Player_Body = {
		type = "Body",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, 0, 0},
		scale = {0.2, 0.2, 0.2},
		--model = "marine.mesh",
		model = "Test_Main_character.mesh",
		material = "Yellow",
		--defaultAnimation = "Idle",
		defaultAnimation = "Idle_cycle_1",
		walkRightAnimation = "Walking_cycle",
		idleAnimation = "Idle_cycle_1",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.01,
		jump_speed = 0.03,
		jump_height = 8.0,
		gravity = 0.015,
		defaultVision = 5,
	},

	Player_Shadow = {
		type = "Shadow",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, 0, -3.5},
		scale = {0.2, 0.2, 0.2},
		--model = "marine.mesh",
		model = "Test_Main_character.mesh",
		material = "Black",
		--defaultAnimation = "Idle",
		defaultAnimation = "Idle_cycle_1",
		walkRightAnimation = "Walking_cycle",
		idleAnimation = "Idle_cycle_1",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 1,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.01,
		jump_speed = 0.03,
		jump_height = 8.0,
		gravity = 0.01,
	},

	Crawler_Body = {
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
		guizmo = false,
		guizmoSize = 10,
		speed = 0.005,
		patrolPosition1 = {0, 0, 0},
		patrolPosition2 = {5, 0, 0},
		fsm_initial_state = "Crawler_Patrol",
	},

	Lightbulb_Body = {
		type = "Body",
		blueprint = "Crawler",
		game_object = "Lightbulb_GO",
		position = {0, -14, 0},
		scale = {0.2, 0.2, 0.2},
		model = "marine.mesh",
		material = "Red",
		defaultAnimation = "Idle",
		walkRightAnimation = "WalkBack",
		idleAnimation = "Idle",
		physic_shape = "capsule",
		physic_radius = 1,
		physic_height = 0.1,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.005,
		patrolPosition1 = {4, -14, 0},
		patrolPosition2 = {10, -14, 0},
		fsm_initial_state = "Lightbulb_Patrol",
	},

	Kasai = {
		type = "Body",
		blueprint = "Kasai",
		game_object = "Kasai_GO",
		position = {0,0,0},
		light_position = {0,0,0},
		specular_colour = {1,1,1},
		diffuse_colour = {1,1,1},
		flare_material = "Flare",
		flare_colour = {1,1,1},
		flare_size = 10,
		light_attenuation_range = 6.5,
		light_attenuation_constant = 1.0,
		light_attenuation_linear = 0.2,
		light_attenuation_quadratic = 0.05,
		player = "Player_GO",
		lighting_area_radius = 6.5,
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
		game_object = "World0_GO",
		prefab = "World_Prefab",
		position = {30, 0, 0},
		scale = {1, 35, 10},
		physic_dimensions = { 1, 35, 10 },
	},
		

	World1 = {
		-- Para que sea un DeathPlane
		physic_type = "kinematic",
		physic_mass = 1,
		blueprint = "DeathPlane",
		-- Fin
		type = "Body",
		game_object = "World1_GO",
		prefab = "World_Prefab",
		position = {0, -25, 0},
		scale = {60, 1, 10},
		physic_dimensions = { 65, 1, 10 },
	},

	World2 = {
		type = "Body",
		game_object = "World2_GO",
		prefab = "World_Prefab",
		position = {0, 17, 0},
		scale = {60, 1, 10},
		physic_dimensions = { 65, 1, 10 },
	},

	World3 = {
		type = "Body",
		game_object = "World3_GO",
		prefab = "World_Prefab",
		position = {-30, 0, 0},
		scale = {1, 35, 10},
		physic_dimensions = { 1, 35, 10 },
	},

	World4 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World4_GO",
		position = {0, 0, -3.5},
		model = "Plane.mesh",
		material = "Rocky",
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