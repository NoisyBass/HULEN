Map_GO = {
	
	Player_GO = {
		type = "GameObject",
		blueprint = "Player_GO",
		isPlayer = true,
		state = "Body",
		playerDeathTime = 3,
		playerCanDie = true,
		kasai = "Kasai_GO",
		charge = "Charge_Prefab",
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

	Spike_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Body",
	},

	--[[DeathPlane_GO = {
		type = "GameObject",
		blueprint = "Empty",
		state = "Both",
	}]]--

}

Map = {

	Player_Body = {
		type = "Body",
		blueprint = "Player",
		--blueprint = "PlayerNoAnimation",
		game_object = "Player_GO",
		position = {-27.8, -14.7, -1},
		--position = {0,10,0}, -- DeathPlane pruebas
		scale = {0.25, 0.25, 0.25},
		orientation = 0,
		model = "marine.mesh",
		--model = "Character003.mesh",
		defaultAnimation = "Idle",
		physic_shape = "capsule",
		physic_radius = 1.5,
		physic_height = 3,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.01,
		jump_speed = 0.04,
		jump_height = 12.0,
		gravity = 0.015,
	},

	Player_Shadow = {
		type = "Shadow",
		blueprint = "Player",
		game_object = "Player_GO",
		position = {-27.8, -14.7, -3.5},
		scale = {0.25, 0.25, 0.25},
		orientation = 0,
		model = "marine.mesh",
		material = "Red",
		defaultAnimation = "Idle",
		physic_shape = "capsule",
		physic_radius = 1.5,
		physic_height = 3,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.01,
		jump_speed = 0.04,
		jump_height = 12.0,
		gravity = 0.015,
	},

	--[[Player_Body = {
		type = "Body",
		blueprint = "PlayerNoAnimation",
		game_object = "Player_GO",
		position = {-27.8, -14.7, 0},
		--position = {0,10,0}, -- DeathPlane pruebas
		scale = {0.05,0.05,0.05},
		orientation = 90,
		model = "Character.mesh",
		physic_shape = "capsule",
		physic_radius = 1.5,
		physic_height = 3,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.01,
		jump_speed = 0.04,
		jump_height = 12.0,
		gravity = 0.015,
	},

	Player_Shadow = {
		type = "Shadow",
		blueprint = "PlayerNoAnimation",
		game_object = "Player_GO",
		position = {-27.8, -14.7, -3.5},
		--position = {0,10,-3.5}, -- DeathPlane pruebas
		scale = {0.05,0.05,0.05},
		orientation = 90,
		model = "Character.mesh",
		material = "Red",
		physic_shape = "capsule",
		physic_radius = 1.5,
		physic_height = 3,
		guizmo = false,
		guizmoSize = 10,
		speed = 0.01,
		jump_speed = 0.04,
		jump_height = 12.0,
		gravity = 0.015,
	},]]--

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
		scale = {0.1, 3.5, 1},
		physic_dimensions = { 0.1, 35, 10 },
	},
		

	World1 = {
		type = "Body",
		game_object = "World1_GO",
		prefab = "World_Prefab",
		position = {0, -17, 0},
		scale = {6, 0.1, 1},
		physic_dimensions = { 65, 0.1, 10 },
	},

	World2 = {
		type = "Body",
		game_object = "World2_GO",
		prefab = "World_Prefab",
		position = {0, 17, 0},
		scale = {6, 0.1, 1},
		physic_dimensions = { 65, 0.1, 10 },
	},

	World3 = {
		type = "Body",
		game_object = "World3_GO",
		prefab = "World_Prefab",
		position = {-30, 0, 0},
		scale = {0.1, 3.5, 1},
		physic_dimensions = { 0.1, 35, 10 },
	},

	World4 = {
		type = "Body",
		blueprint = "Background",
		game_object = "World4_GO",
		position = {0, 0, -3.5},
		model = "Plane.mesh",
		material = "Rocky",
	},

	Spike = {
		type = "Body",
		blueprint = "Spike",
		game_object = "Spike_GO",
		position = {0,-15,0},
		model = "Spike.mesh",
		static = true,
		physic_entity = "fromFile",
		physic_file = "media/models/Spike.RepX",
		physic_group = 1,
	},

--[[DeathPlane_Body = {
		type = "Body",
		blueprint = "DeathPlane",
		game_object = "DeathPlane_GO",
		position = {-10, 0, 0},
		scale = {6, 0.1, 1},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_mass = 1,
		physic_shape = "box",
		physic_dimensions = { 65, 0.1, 10 },
		physic_height = 1,
		physic_group = 1,
		material = "Rocky",
	},

	DeathPlane_Shadow = {
		type = "Shadow",
		blueprint = "DeathPlane",
		game_object = "DeathPlane_GO",
		position = {-10, 0, 0},
		scale = {6, 0.1, 1},
		model = "Cube.mesh",
		physic_entity = "rigid",
		physic_type = "kinematic",
		physic_mass = 1,
		physic_shape = "box",
		physic_dimensions = { 65, 0.1, 10 },
		physic_height = 1,
		physic_group = 1,
		material = "Rocky",
	},]]--
}