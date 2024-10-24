.set LOCALID_TWIN, 1
.set LOCALID_MOM, 4
.set LOCALID_RIVAL, 7
.set LOCALID_BIRCH, 8

LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LittlerootTown_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, LittlerootTown_OnWarp
	.byte 0

	@ State descriptions for VAR_LITTLEROOT_TOWN_STATE
	@ 1: Met Rival
	@ 2: Saving Birch
	@ 3: Received Pokedex
	@ 4: Received Running Shoes

	@ State descriptions for VAR_LITTLEROOT_INTRO_STATE
	@ 1: In truck male
	@ 2: In truck female
	@ 3: Entered house
	@ 4: Told to go set clock
	@ 5: Entered 2F to set clock
	@ 6: Set clock
	@ 7: Told to go meet rival

	@ State descriptions for VAR_LITTLEROOT_HOUSES_STATE_MAY
	@                    and VAR_LITTLEROOT_HOUSES_STATE_BRENDAN
	@ 1: On Truck (and is corresponding gender)
	@ 2: Met Rival's Mom (and is corresponding gender)
	@ 3: Entered Hall of Fame
	@ 4: Completed Lati TV / SS Ticket event
	@ 5: Exited house after above event

	@ State descriptions for VAR_LITTLEROOT_RIVAL_STATE
	@ 1: Never occurs
	@ 2: Entered Rival's bedroom
	@ 3: Met Rival
	@ 4: Received Pokedex


LittlerootTown_OnTransition:
	setflag FLAG_VISITED_LITTLEROOT_TOWN
	call Common_EventScript_SetupRivalGfxId
	call_if_eq VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_MoveMomToMaysDoor
	call_if_unset FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_SetTwinPos
	call_if_eq VAR_LITTLEROOT_TOWN_STATE, 3, LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_MAY, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 4, LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent
	call_if_eq VAR_OLDALE_RIVAL_STATE, 1, LittlerootTown_EventScript_MoveRivalFromOldale
	call_if_eq VAR_LITTLEROOT_RIVAL_STATE, 3, LittlerootTown_EventScript_SetRivalLeftForRoute103
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_HideMapNamePopup
	call_if_eq VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 2, LittlerootTown_EventScript_LeftLabAfterDexUpgrade
	end

LittlerootTown_EventScript_LeftLabAfterDexUpgrade::
	setvar VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 3
	return

LittlerootTown_EventScript_HideMapNamePopup::
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_EventScript_SetRivalLeftForRoute103::
	setflag FLAG_RIVAL_LEFT_FOR_ROUTE103
	return

LittlerootTown_EventScript_MoveRivalFromOldale::
	setvar VAR_OLDALE_RIVAL_STATE, 2
	setflag FLAG_HIDE_OLDALE_TOWN_RIVAL
	return

LittlerootTown_EventScript_SetExitedHouseAfterLatiSSTicketEvent::
	setvar VAR_LITTLEROOT_HOUSES_STATE_MAY, 5
	setvar VAR_LITTLEROOT_HOUSES_STATE_BRENDAN, 5
	return

LittlerootTown_EventScript_MoveMomToMaysDoor::
	setobjectxyperm LOCALID_MOM, 14, 8
	return

LittlerootTown_EventScript_SetTwinPos::
	goto_if_eq VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_SetTwinGuardingRoutePos
	setobjectxyperm LOCALID_TWIN, 10, 1
	setobjectmovementtype LOCALID_TWIN, MOVEMENT_TYPE_FACE_UP
	return

LittlerootTown_EventScript_SetTwinGuardingRoutePos::
	setobjectxyperm LOCALID_TWIN, 7, 2
	setobjectmovementtype LOCALID_TWIN, MOVEMENT_TYPE_FACE_DOWN
	return

LittlerootTown_EventScript_SetMomStandingInFrontOfDoorPos::
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setobjectmovementtype LOCALID_MOM, MOVEMENT_TYPE_FACE_DOWN
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetMomInFrontOfDoorMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetMomInFrontOfDoorFemale
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorMale::
	setobjectxyperm LOCALID_MOM, 5, 9
	return

LittlerootTown_EventScript_SetMomInFrontOfDoorFemale::
	setobjectxyperm LOCALID_MOM, 14, 9
	return

LittlerootTown_OnFrame:
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 1, LittlerootTown_EventScript_StepOffTruckMale
	map_script_2 VAR_LITTLEROOT_INTRO_STATE, 2, LittlerootTown_EventScript_StepOffTruckFemale
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_BeginDexUpgradeScene
	.2byte 0

LittlerootTown_EventScript_StepOffTruckMale::
	lockall
	setvar VAR_0x8004, 5
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_BRENDANS_HOUSE_1F, 8, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_StepOffTruckFemale::
	lockall
	setvar VAR_0x8004, 14
	setvar VAR_0x8005, 8
	call LittlerootTown_EventScript_GoInsideWithMom
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_TRUCK
	warpsilent MAP_LITTLEROOT_TOWN_MAYS_HOUSE_1F, 2, 8
	waitstate
	releaseall
	end

LittlerootTown_EventScript_GoInsideWithMom::
	delay 15
	playse SE_LEDGE
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerStepOffTruck
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	addobject LOCALID_MOM
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitHouse
	waitmovement 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	delay 10
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerAtTruck
	waitmovement 0
	msgbox LittlerootTown_Text_OurNewHomeLetsGoInside, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachDoor
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerApproachDoor
	waitmovement 0
	opendoor VAR_0x8004, VAR_0x8005
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomEnterHouse
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PlayerEnterHouse
	waitmovement 0
	setflag FLAG_HIDE_LITTLEROOT_TOWN_MOM_OUTSIDE
	setvar VAR_LITTLEROOT_INTRO_STATE, 3
	hideobjectat OBJ_EVENT_ID_PLAYER, 0
	closedoor VAR_0x8004, VAR_0x8005
	waitdooranim
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_FAT_MAN
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	return

LittlerootTown_Movement_MomExitHouse:
	walk_down
	step_end

LittlerootTown_Movement_MomApproachPlayerAtTruck:
	walk_down
	walk_in_place_faster_left
	step_end

LittlerootTown_Movement_MomApproachDoor:
	delay_16
	delay_8
	walk_up
	step_end

LittlerootTown_Movement_MomEnterHouse:
	walk_up
	set_invisible
	step_end

LittlerootTown_Movement_PlayerApproachDoor:
	delay_16
	delay_8
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_PlayerEnterHouse:
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_PlayerStepOffTruck:
	jump_right
	delay_16
	delay_16
	delay_16
	step_end

LittlerootTown_EventScript_BeginDexUpgradeScene::
	lockall
	playse SE_PIN
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
	waitmovement 0
	delay 80
	msgbox LittlerootTown_Text_BirchSomethingToShowYouAtLab, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_RIVAL
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BIRCH
	delay 20
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_LITTLEROOT_TOWN_PROFESSOR_BIRCHS_LAB, 6, 5
	waitstate
	releaseall
	end

LittlerootTown_OnWarp:
	map_script_2 VAR_DEX_UPGRADE_JOHTO_STARTER_STATE, 1, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade
	.2byte 0

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgrade::
	addobject LOCALID_BIRCH
	addobject LOCALID_RIVAL
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale
	goto LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeMale::
	setobjectxy LOCALID_RIVAL, 6, 10
	setobjectxy LOCALID_BIRCH, 5, 10
	end

LittlerootTown_EventScript_SetRivalBirchPosForDexUpgradeFemale::
	setobjectxy LOCALID_RIVAL, 13, 10
	setobjectxy LOCALID_BIRCH, 14, 10
	end

LittlerootTown_EventScript_FatMan::
	msgbox LittlerootTown_Text_CanUsePCToStoreItems, MSGBOX_NPC
	end

LittlerootTown_EventScript_Boy::
	msgbox LittlerootTown_Text_BirchSpendsDaysInLab, MSGBOX_NPC
	end

LittlerootTown_EventScript_Twin::
	lock
	faceplayer
	goto_if_set FLAG_ADVENTURE_STARTED, LittlerootTown_EventScript_GoodLuck
	goto_if_set FLAG_RESCUED_BIRCH, LittlerootTown_EventScript_YouSavedBirch
	goto_if_ne VAR_LITTLEROOT_TOWN_STATE, 0, LittlerootTown_EventScript_GoSaveBirch
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoSaveBirch::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	release
	end

LittlerootTown_EventScript_YouSavedBirch::
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_YouSavedBirch, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_GoodLuck::
	msgbox LittlerootTown_Text_GoodLuckCatchingPokemon, MSGBOX_DEFAULT
	release
	end

LittlerootTown_EventScript_NeedPokemonTriggerLeft::
	lockall
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinApproachPlayerLeft
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinReturnLeft
	waitmovement 0
	releaseall
	end

LittlerootTown_EventScript_DangerousWithoutPokemon::
	msgbox LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinPushPlayerFromRoute
	applymovement OBJ_EVENT_ID_PLAYER, LittlerootTown_Movement_PushPlayerBackFromRoute
	waitmovement 0
	msgbox LittlerootTown_Text_DangerousIfYouDontHavePokemon, MSGBOX_DEFAULT
	closemessage
	return

LittlerootTown_Movement_TwinApproachPlayerLeft:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_left
	face_down
	step_end

LittlerootTown_Movement_TwinPushPlayerFromRoute:
	walk_down
	step_end

LittlerootTown_Movement_TwinReturnLeft:
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_in_place_faster_down
	step_end

LittlerootTown_Movement_PushPlayerBackFromRoute:
	lock_facing_direction
	walk_down
	unlock_facing_direction
	step_end

LittlerootTown_EventScript_NeedPokemonTriggerRight::
	lockall
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinApproachPlayerRight
	waitmovement 0
	call LittlerootTown_EventScript_DangerousWithoutPokemon
	applymovement LOCALID_TWIN, LittlerootTown_Movement_TwinReturnRight
	waitmovement 0
	releaseall
	end

LittlerootTown_Movement_TwinApproachPlayerRight:
	face_right
	delay_8
	disable_jump_landing_ground_effect
	jump_in_place_right
	delay_8
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_right
	face_down
	step_end

LittlerootTown_Movement_TwinReturnRight:
	walk_left
	walk_down
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_down
	step_end

LittlerootTown_EventScript_GoSaveBirchTrigger::
	lockall
	applymovement LOCALID_TWIN, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	special GetPlayerBigGuyGirlString
	msgbox LittlerootTown_Text_CanYouGoSeeWhatsHappening, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_TWIN, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setvar VAR_LITTLEROOT_TOWN_STATE, 2
	releaseall
	end

LittlerootTown_EventScript_TownSign::
	msgbox LittlerootTown_Text_TownSign, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BirchsLabSign::
	msgbox LittlerootTown_Text_ProfBirchsLab, MSGBOX_SIGN
	end

LittlerootTown_EventScript_BrendansHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_PlayersHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_BirchsHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_PlayersHouseSignMale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_BirchsHouseSignFemale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_MaysHouseSign::
	lockall
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_BirchsHouseSignMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_PlayersHouseSignFemale
	releaseall
	end

LittlerootTown_EventScript_BirchsHouseSignMale::
	msgbox LittlerootTown_Text_ProfBirchsHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_PlayersHouseSignFemale::
	msgbox LittlerootTown_Text_PlayersHouse, MSGBOX_DEFAULT
	return

LittlerootTown_EventScript_GiveRunningShoesTrigger0::
	lockall
	setvar VAR_0x8008, 0
	setobjectxy LOCALID_MOM, 10, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger1::
	lockall
	setvar VAR_0x8008, 1
	setobjectxy LOCALID_MOM, 11, 9
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger2::
	lockall
	setvar VAR_0x8008, 2
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger3::
	lockall
	setvar VAR_0x8008, 3
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger4::
	lockall
	setvar VAR_0x8008, 4
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger5::
	lockall
	setvar VAR_0x8008, 5
	goto LittlerootTown_EventScript_GiveRunningShoesTrigger
	end

LittlerootTown_EventScript_GiveRunningShoesTrigger::
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomNoticePlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomNoticePlayerFemale
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	msgbox LittlerootTown_Text_WaitPlayer, MSGBOX_DEFAULT
	closemessage
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomApproachPlayerMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomApproachPlayerFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_MomReturnHomeMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_MomReturnHomeFemale
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetHomeDoorCoordsMale::
	setvar VAR_0x8009, 5
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_SetHomeDoorCoordsFemale::
	setvar VAR_0x8009, 14
	setvar VAR_0x800A, 8
	return

LittlerootTown_EventScript_MomNoticePlayerMale::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	return

LittlerootTown_EventScript_MomNoticePlayerFemale::
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerMale5
	return

LittlerootTown_EventScript_MomApproachPlayerFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomApproachPlayer0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomApproachPlayer1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomApproachPlayerFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomApproachPlayerFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomApproachPlayerFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomApproachPlayerFemale5
	return

LittlerootTown_EventScript_MomApproachPlayer0::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayer0
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayer1::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayer1
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale2::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale4::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerMale5::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerMale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale2::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale2
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale3::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale3
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale4::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale4
	waitmovement 0
	return

LittlerootTown_EventScript_MomApproachPlayerFemale5::
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomApproachPlayerFemale5
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeMale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeMale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeMale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeMale5
	return

LittlerootTown_EventScript_MomReturnHomeFemale::
	call_if_eq VAR_0x8008, 0, LittlerootTown_EventScript_MomReturnHome0
	call_if_eq VAR_0x8008, 1, LittlerootTown_EventScript_MomReturnHome1
	call_if_eq VAR_0x8008, 2, LittlerootTown_EventScript_MomReturnHomeFemale2
	call_if_eq VAR_0x8008, 3, LittlerootTown_EventScript_MomReturnHomeFemale3
	call_if_eq VAR_0x8008, 4, LittlerootTown_EventScript_MomReturnHomeFemale4
	call_if_eq VAR_0x8008, 5, LittlerootTown_EventScript_MomReturnHomeFemale5
	return

LittlerootTown_EventScript_MomReturnHome0::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHome0
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHome1::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHome1
	waitmovement 0
	return

LittlerootTown_EventScript_MomReturnHomeMale2::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale3::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale4::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeMale5::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeMale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale2::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale2
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale3::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale3
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale4::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale4
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_EventScript_MomReturnHomeFemale5::
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomReturnHomeFemale5
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	return

LittlerootTown_Movement_MomApproachPlayer0:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayer1:
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	walk_up
	step_end

LittlerootTown_Movement_MomApproachPlayerMale2:
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale3:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale4:
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerMale5:
	walk_right
	walk_right
	walk_right
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale2:
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale3:
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale4:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomApproachPlayerFemale5:
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LittlerootTown_Movement_MomReturnHome0:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHome1:
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

LittlerootTown_Movement_MomReturnHomeMale2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale3:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale4:
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeMale5:
	walk_left
	walk_left
	walk_left
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale2:
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale3:
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale4:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomReturnHomeFemale5:
	walk_right
	walk_right
	walk_right
	walk_right
	walk_in_place_faster_up
	step_end

LittlerootTown_Movement_MomExitThroughDoor:
	walk_up
	step_end

LittlerootTown_EventScript_Mom::
	lock
	faceplayer
	checkplayergender
	call_if_eq VAR_RESULT, MALE, LittlerootTown_EventScript_SetHomeDoorCoordsMale
	call_if_eq VAR_RESULT, FEMALE, LittlerootTown_EventScript_SetHomeDoorCoordsFemale
	call LittlerootTown_EventScript_GiveRunningShoes
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterUp
	waitmovement 0
	opendoor VAR_0x8009, VAR_0x800A
	waitdooranim
	applymovement LOCALID_MOM, LittlerootTown_Movement_MomExitThroughDoor
	waitmovement 0
	hideobjectat LOCALID_MOM, MAP_LITTLEROOT_TOWN
	closedoor VAR_0x8009, VAR_0x800A
	waitdooranim
	goto LittlerootTown_EventScript_SetReceivedRunningShoes
	end

LittlerootTown_EventScript_SetReceivedRunningShoes::
	removeobject LOCALID_MOM
	setflag FLAG_SYS_B_DASH
	setvar VAR_LITTLEROOT_TOWN_STATE, 4
	release
	end

LittlerootTown_EventScript_GiveRunningShoes::
	msgbox LittlerootTown_Text_WearTheseRunningShoes, MSGBOX_DEFAULT
	playfanfare MUS_OBTAIN_ITEM
	message LittlerootTown_Text_SwitchShoesWithRunningShoes
	waitfanfare
	setflag FLAG_RECEIVED_RUNNING_SHOES
	msgbox LittlerootTown_Text_ExplainRunningShoes, MSGBOX_DEFAULT
	msgbox LittlerootTown_Text_ComeHomeIfAnythingHappens, MSGBOX_DEFAULT
	closemessage
	delay 30
	return

LittlerootTown_Text_OurNewHomeLetsGoInside:
	.string "MOM: {PLAYER}, we're here, honey!\p"
	.string "It must be tiring riding with our things\n"
	.string "in the moving truck.\p"
	.string "Well, this is LITTLEROOT TOWN.\p"
	.string "How do you like it?\n"
	.string "This is our new home!\p"
	.string "It has a quaint feel, but it seems to be\n"
	.string "an easy place to live, don't you think?\p"
	.string "And, you get your own room, {PLAYER}!\n"
	.string "Let's go inside.$"

LittlerootTown_Text_WaitPlayer:
	.string "MOM: Wait, {PLAYER}!$"

LittlerootTown_Text_WearTheseRunningShoes:
	.string "MOM: {PLAYER}! {PLAYER}! Did you\n"
	.string "introduce yourself to PROF. BIRCH?\p"
	.string "Oh! What an adorable POKéMON!\n"
	.string "You got it from PROF. BIRCH. How nice!\p"
	.string "You're your father's child, all right.\n"
	.string "You look good together with POKéMON!\p"
	.string "Here, honey! If you're going out on an\n"
	.string "adventure, wear these RUNNING SHOES.\p"
	.string "They'll put a zip in your step!$"

LittlerootTown_Text_SwitchShoesWithRunningShoes:
	.string "{PLAYER} switched shoes with the\n"
	.string "RUNNING SHOES.$"

LittlerootTown_Text_ExplainRunningShoes:
	.string "MOM: {PLAYER}, those shoes came with\n"
	.string "instructions.\p"
	.string "“Press the B Button while wearing these\n"
	.string "RUNNING SHOES to run extra-fast!\p"
	.string "“Slip on these RUNNING SHOES and race\n"
	.string "in the great outdoors!”$"

LittlerootTown_Text_ComeHomeIfAnythingHappens:
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "To think that you have your very own\n"
	.string "POKéMON now…\l"
	.string "Your father will be overjoyed.\p"
	.string "…But please be careful.\n"
	.string "If anything happens, you can come home.\p"
	.string "Go on, go get them, honey!$"

LittlerootTown_Text_CanUsePCToStoreItems:
	.string "If you use a PC, you can store items\n"
	.string "and POKéMON.\p"
	.string "The power of science is staggering!$"

LittlerootTown_Text_BirchSpendsDaysInLab:
	.string "PROF. BIRCH spends days in his LAB\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does PROF. BIRCH spend time\n"
	.string "at home?$"

LittlerootTown_Text_IfYouGoInGrassPokemonWillJumpOut:
	.string "Um, um, um!\p"
	.string "If you go outside and go in the grass,\n"
	.string "wild POKéMON will jump out!$"

LittlerootTown_Text_DangerousIfYouDontHavePokemon:
	.string "It's dangerous if you don't have\n"
	.string "your own POKéMON.$"

LittlerootTown_Text_CanYouGoSeeWhatsHappening:
	.string "Um, hi!\p"
	.string "There are scary POKéMON outside!\n"
	.string "I can hear their cries!\p"
	.string "I want to go see what's going on,\n"
	.string "but I don't have any POKéMON…\p"
	.string "Can you go see what's happening\n"
	.string "for me?$"

LittlerootTown_Text_YouSavedBirch:
	.string "You saved PROF. BIRCH!\n"
	.string "I'm so glad!$"

LittlerootTown_Text_GoodLuckCatchingPokemon:
	.string "Are you going to catch POKéMON?\n"
	.string "Good luck!$"

LittlerootTown_Text_TownSign:
	.string "LITTLEROOT TOWN\n"
	.string "“A town that can't be shaded any hue.”$"

LittlerootTown_Text_ProfBirchsLab:
	.string "PROF. BIRCH'S POKéMON LAB$"

LittlerootTown_Text_PlayersHouse:
	.string "{PLAYER}'s HOUSE$"

LittlerootTown_Text_ProfBirchsHouse:
	.string "PROF. BIRCH'S HOUSE$"

LittlerootTown_Text_BirchSomethingToShowYouAtLab:
	.string "PROF. BIRCH: Well, well, {PLAYER}{KUN}!\n"
	.string "That was good work out there!\p"
	.string "I knew there was something special\n"
	.string "about you when I first saw you,\l"
	.string "but I never expected this.\p"
	.string "Oh, yes. Do you still have the POKéDEX\n"
	.string "I gave you?\p"
	.string "I have something to show you.\n"
	.string "Let's go to my LAB.$"

LilycoveCity_GTS_F1_EventScript_ScammedGuy::
	msgbox LilycoveCity_GTS_F1_Text_ITradedMyShiny, MSGBOX_NPC
	end

LilycoveCity_GTS_F1_EventScript_ScienceGuy::
	msgbox LilycoveCity_GTS_F1_Text_TheUnderSeaCables, MSGBOX_NPC
	end

LilycoveCity_GTS_F1_EventScript_SmallWorldGran::
	msgbox LilycoveCity_GTS_F1_Text_ItsSoEasyToConnect, MSGBOX_NPC
	end

LilycoveCity_GTS_F1_EventScript_MailGirl::
	lock
	faceplayer
	goto_if_eq VAR_TEMP_1, 1, LilycoveCity_GTS_F1_MailGirlItemGiven
	msgbox LilycoveCity_GTS_F1_Text_WhenMyFriendMoved, MSGBOX_DEFAULT
	random 12
	addvar VAR_RESULT, FIRST_MAIL_INDEX
	giveitem VAR_RESULT
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setvar VAR_TEMP_1, 1
	msgbox LilycoveCity_GTS_F1_Text_YouCanHaveThis, MSGBOX_DEFAULT
	release
	end

LilycoveCity_GTS_F1_MailGirlItemGiven::
	msgbox LilycoveCity_GTS_F1_Text_YouCanHaveThis, MSGBOX_DEFAULT
	release
	end

LilycoveCity_GTS_F1_EventScript_Receptionist::
	lock
	faceplayer
	msgbox LilycoveCity_GTS_F1_Text_Info, MSGBOX_NPC
	releaseall
	end
	
LilycoveCity_GTS_F1_EventScript_DeskMonitor::
	message LilycoveCity_GTS_F1_EventScript_ShouldStartConnection
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, LilycoveCity_GTS_F1_EventScript_DontDisplayConnectionStatus
	case 0, LilycoveCity_GTS_F1_EventScript_TryDisplayConnectionStatus
	case MULTI_B_PRESSED, LilycoveCity_GTS_F1_EventScript_DontDisplayConnectionStatus

LilycoveCity_GTS_F1_EventScript_ProfileGuy::
	lock
	faceplayer
	msgbox ProfileMan_Text_OnlineSafety, MSGBOX_DEFAULT
	goto_if_set FLAG_SYS_CHAT_USED, ProfileMan_EventScript_AskToSeeNewProfile
	goto ProfileMan_EventScript_AskToSeeProfile
	end

LilycoveCity_GTS_F1_EventScript_ResultScreen::
	msgbox LilycoveCity_GTS_F1_Text_Version, MSGBOX_NPC
	releaseall
	end

LilycoveCity_GTS_F1_EventScript_DontDisplayConnectionStatus::
	release
	end

@special CallNetworkFunction
LilycoveCity_GTS_F1_EventScript_TryDisplayConnectionStatus::
	message LilycoveCity_GTS_F1_PleaseWaitForLink
	waitmessage
	setvar VAR_0x8004, NET_CONN_START_LINK_FUNC
	special CallNetworkFunction
	waitstate
	call LilycoveCity_GTS_F1_EventScript_GetConnectionStatusText
	lock
	message LilycoveCity_GTS_F1_EventScript_ConnectionStatusMessage
	waitmessage
	goto_if_eq VAR_0x8003, 2, LilycoveCity_GTS_F1_EventScript_ServerWelcome
	waitbuttonpress
	closemessage
	release
	end

LilycoveCity_GTS_F1_EventScript_ConnectionStatusMessage::
	.string "Connection Status: \n{STR_VAR_2}$"


LilycoveCity_GTS_F1_EventScript_ServerWelcome::
	waitmessage
	waitbuttonpress
	msgbox gStringVar3, MSGBOX_DEFAULT
	waitmessage
	closemessage
	release
	end

LilycoveCity_GTS_F1_EventScript_GetConnectionStatusText::
	goto_if_eq VAR_0x8003, 1, LilycoveCity_GTS_F1_EventScript_SetConnectionStatusLocal
	goto_if_eq VAR_0x8003, 2, LilycoveCity_GTS_F1_EventScript_SetConnectionStatusOnline
	bufferstring STR_VAR_2, LilycoveCity_GTS_F1_EventScript_Text_ConnectinoFailed
	return

LilycoveCity_GTS_F1_EventScript_SetConnectionStatusLocal::
	bufferstring STR_VAR_2, LilycoveCity_GTS_F1_EventScript_Text_ConnectionLocal
	return

LilycoveCity_GTS_F1_EventScript_SetConnectionStatusOnline::
	bufferstring STR_VAR_2, LilycoveCity_GTS_F1_EventScript_Text_ConnectionOnline
	return

LilycoveCity_GTS_F1_EventScript_ShouldStartConnection::
	.string "Start Pokecom channel connection?$"

LilycoveCity_GTS_F1_Text_ITradedMyShiny::
	.string "I traded my shiny KADABRA to\n"
	.string "a cute girl I met online.\p"
	.string "Her phone must have broken because\n"
	.string "she's not returning my calls…$"

LilycoveCity_GTS_F1_Text_TheUnderSeaCables::
	.string "The under-sea network cables go\n"
	.string "all the way to GOLDENROD.\p"
	.string "Special ships called cable-layers\n"
	.string "sink them to the ocean floor.$"

LilycoveCity_GTS_F1_Text_ItsSoEasyToConnect::
	.string "Connecting to others has become\p"
	.string "so simple.\p"
	.string "Is it my age or does the world feel\n"
	.string "smaller now?$"

LilycoveCity_GTS_F1_Text_WhenMyFriendMoved::
	.string "When my friend moved to KANTO I thought\n"
	.string "we wouldn't be able to talk anymore.\p"
	.string "Thanks to the INTERNET we can \n"
	.string "send messages every day!\p"
	.string "You can have this.$"

LilycoveCity_GTS_F1_Text_YouCanHaveThis::
	.string "By sending mail maybe you can make\n"
	.string "friends too.$"

LilycoveCity_GTS_F1_PleaseWaitForLink::
	.string "Please wait.\n"
	.string "… … Hold B Button: Cancel$"

LilycoveCity_GTS_F1_EventScript_Text_ConnectinoFailed:
	.string "{COLOR RED}{SHADOW LIGHT_RED}FAILED$"

LilycoveCity_GTS_F1_EventScript_Text_ConnectionLocal:
	.string "{COLOR BLUE}{SHADOW LIGHT_BLUE}PLUGGED IN - NO INTERNET$"

LilycoveCity_GTS_F1_EventScript_Text_ConnectionOnline:
	.string "{COLOR GREEN}{SHADOW LIGHT_GREEN}ONLINE$"

LilycoveCity_GTS_F1_Text_Version::
	.string "Emerald Net Demo 0.1.2$"

LilycoveCity_GTS_F1_Text_Info::
	.string "Welcome to LILYCOVE NETWORK CENTER!\n"
	.string "You can get connected with the\l"
	.string "terminal on the left.\p" 
	.string "Through the door behind me you can find\n"
	.string "network demos to try when connected.$"

ProfileMan_Text_OnlineSafety::
	.string "Did you know that your profile can\n"
	.string "help you stay safe while online?\p"
	.string "If a trainers profile starts with\n"
	.string "{COLOR BLUE}{SHADOW LIGHT_BLUE}FRIEND LINK {COLOR DARK_GRAY}{SHADOW LIGHT_GRAY}then they'll only link\l"
	.string "to players with a matching profile.\p"
	.string "Actually, my hobby is collecting the\n"
	.string "profiles of POKéMON TRAINERS.$"

	// FLR2

	LilycoveCity_GTS_F2_EventScript_UnionLady::
	lock
	faceplayer
	msgbox LilycoveCity_GTS_F2_Text_DoYouWantToRandomTrade, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, LilycoveCity_GTS_F2_EventScript_DeclineTrade
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x8005, VAR_0x8004
	goto_if_eq VAR_0x8005, PARTY_NOTHING_CHOSEN, LilycoveCity_GTS_F2_EventScript_DeclineTrade
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	copyvar VAR_0x8009, VAR_RESULT
	bufferspeciesname STR_VAR_1, VAR_0x8009
	message LilycoveCity_GTS_F2_Text_PleaseConfirmTrade
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, LilycoveCity_GTS_F2_EventScript_DeclineTrade
	case 0, LilycoveCity_GTS_F2_EventScript_Trade
	case MULTI_B_PRESSED, LilycoveCity_GTS_F2_EventScript_DeclineTrade
	end

LilycoveCity_GTS_F2_EventScript_Trainer::
	lock
	faceplayer
	message LilycoveCity_GTS_F2_Text_StartDownloadBattle
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, LilycoveCity_GTS_F2_EventScript_DontConnect
	case 0, LilycoveCity_GTS_F2_EventScript_NetTrainer
	case MULTI_B_PRESSED, LilycoveCity_GTS_F2_EventScript_DontConnect
	end

LilycoveCity_GTS_F2_EventScript_NetTrainer::
	setvar VAR_0x8004, NET_CONN_START_BATTLE_FUNC
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	setvar VAR_0x8004, SPECIAL_BATTLE_EREADER
	setvar VAR_0x8005, 0
	special DoSpecialTrainerBattle
	waitstate
	frontier_restorehelditems
	special HealPlayerParty
	closemessage
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_MartClerk::
	lock
	faceplayer
	message LilycoveCity_GTS_F2_Text_StartDownloadMart
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, LilycoveCity_GTS_F2_EventScript_DontConnect
	case 0, LilycoveCity_GTS_F2_EventScript_NetShop
	case MULTI_B_PRESSED, LilycoveCity_GTS_F2_EventScript_DontConnect
	end

LilycoveCity_GTS_F2_EventScript_Trade::
	message LilycoveCity_GTS_F2_Text_TradePleaseWait
	setvar VAR_0x8004, NET_CONN_TRADE_FUNC
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	goto_if_eq VAR_0x8003, 1, LilycoveCity_GTS_F2_EventScript_NoPartner
	special DoInGameTradeScene
	waitstate
	release
	end

LilycoveCity_GTS_F2_EventScript_TradeRetry::
	setvar VAR_0x8004, NET_CONN_RETRY_TRADE_FUNC
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	goto_if_eq VAR_0x8003, 1, LilycoveCity_GTS_F2_EventScript_NoPartner
	special DoInGameTradeScene
	waitstate
	release
	end

LilycoveCity_GTS_F2_EventScript_NetShop::
	setvar VAR_0x8004, NET_CONN_START_MART_FUNC
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	closemessage
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_OldGuy::
	lock
	faceplayer
	message LilycoveCity_GTS_F2_Text_StartDownloadEgg
	waitmessage
	multichoicedefault 20, 8, MULTI_YESNO, 1, FALSE
	switch VAR_RESULT
	case 1, LilycoveCity_GTS_F2_EventScript_DontConnect
	case 0, LilycoveCity_GTS_F2_EventScript_NetEgg
	case MULTI_B_PRESSED, LilycoveCity_GTS_F2_EventScript_DontConnect
	end

LilycoveCity_GTS_F2_EventScript_NetEgg::
	specialvar VAR_GIFT_PICHU_SLOT, CalculatePlayerPartyCount
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, LilycoveCity_GTS_F2_EventScript_NoRoomForEgg
	setvar VAR_0x8004, NET_CONN_START_EGG_FUNC
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	goto_if_eq VAR_0x8003, SPECIES_EGG, LilycoveCity_GTS_F2_EventScript_AlreadyObtained
	playfanfare MUS_OBTAIN_ITEM
	msgbox LilycoveCity_GTS_F2_Text_TakeGoodCareOfEgg, MSGBOX_DEFAULT
	waitfanfare
	giveegg VAR_0x8003
	setmonmetlocation VAR_GIFT_PICHU_SLOT, METLOC_FATEFUL_ENCOUNTER
	goto_if_eq VAR_0x8005, MOVE_NONE, LilycoveCity_GTS_F2_EventScript_NetEgg_No_Special_Move
	setmonmove VAR_GIFT_PICHU_SLOT, 3, VAR_0x8005
	closemessage
	releaseall
	end

// LilycoveCity_GTS_F2_EventScript_MailMan::
// 	lock
// 	faceplayer
// 	message LilycoveCity_GTS_F2_Text_MailMan
// 	waitmessage
// 	multichoicedefault 20, 8, MULTI_NET_MAIL, 2, FALSE
// 	switch VAR_RESULT
// 	case 0, LilycoveCity_GTS_F2_EventScript_PostMail
// 	case 1, LilycoveCity_GTS_F2_EventScript_ReadMail
// 	case 2, LilycoveCity_GTS_F2_EventScript_CloseMail
// 	case MULTI_B_PRESSED, LilycoveCity_GTS_F2_EventScript_CloseMail
// 	end

LilycoveCity_GTS_F2_EventScript_PostMail::
	message LilycoveCity_GTS_F2_Text_SelectMailMon
	waitbuttonpress
	special ChoosePartyMon
	waitstate
	copyvar VAR_0x8005, VAR_0x8004
	goto_if_eq VAR_0x8005, PARTY_NOTHING_CHOSEN, LilycoveCity_GTS_F2_EventScript_CloseMail
	setvar VAR_0x8004, NET_CONN_POST_MAIL
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	goto_if_eq VAR_0x8003, 1, LilycoveCity_GTS_F2_EventScript_MonHadNoMail
	message LilycoveCity_GTS_F2_Text_MailSent
	waitmessage
	waitbuttonpress
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_ReadMail::
	setvar VAR_0x8004, NET_CONN_READ_MAIL
	special CallNetworkFunction
	waitstate
	goto_if_eq VAR_0x8003, 0, LilycoveCity_GTS_F2_EventScript_ConnectionEnded
	goto_if_eq VAR_0x8003, 1, LilycoveCity_GTS_F2_EventScript_NoMailFound
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_CloseMail::
	closemessage
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_NetEgg_No_Special_Move::
	closemessage
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_DeclineTrade::
	closemessage
	releaseall
	end

LilycoveCity_GTS_F2_EventScript_NoPartner::
	msgbox LilycoveCity_GTS_F2_Text_NoPartner, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, LilycoveCity_GTS_F2_EventScript_TradeRetry
	closemessage
	end

LilycoveCity_GTS_F2_EventScript_ConnectionEnded::
	msgbox LilycoveCity_GTS_F2_Text_ConnectionEnded, MSGBOX_NPC
	end

LilycoveCity_GTS_F2_Text_ConnectionEnded::
	.string "{COLOR LIGHT_RED}{SHADOW LIGHT_RED}CHECK CONNECTION.$"

LilycoveCity_GTS_F2_EventScript_AlreadyObtained::
	msgbox LilycoveCity_GTS_F2_Text_AlreadyObtained, MSGBOX_NPC
	end

LilycoveCity_GTS_F2_EventScript_NoRoomForEgg::
	msgbox LilycoveCity_GTS_F2_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LilycoveCity_GTS_F2_EventScript_MonHadNoMail::
	msgbox LilycoveCity_GTS_F2_Text_MonHadNoMail, MSGBOX_DEFAULT
	release
	end

LilycoveCity_GTS_F2_EventScript_NoMailFound::
	msgbox LilycoveCity_GTS_F2_Text_NoMailFound, MSGBOX_DEFAULT
	release
	end

LilycoveCity_GTS_F2_Text_NotAvailable::
	.string "This feature is not yet available.$"

LilycoveCity_GTS_F2_Text_TradePleaseWait::
	.string "Preparing trade...$"

LilycoveCity_GTS_F2_Text_DoYouWantToRandomTrade::
	.string "Do you want to randomly trade with\n"
	.string "another player on this server?$"

LilycoveCity_GTS_F2_Text_PleaseConfirmTrade::
	.string "So you want to trade {STR_VAR_1}?\n"
	.string "YOU WON'T BE ABLE TO CANCEL THIS!$"

LilycoveCity_GTS_F2_Text_NoPartner::
	.string "No trade partner found.\n"
	.string "Do you want to search again?$"

LilycoveCity_GTS_F2_Text_TakeGoodCareOfEgg::
	.string "Take good care of the EGG.$"

LilycoveCity_GTS_F2_Text_AlreadyObtained::
	.string "It seems you have already obtained\n"
	.string "this gift egg before.$"

LilycoveCity_GTS_F2_Text_NoRoomForThisEgg::
	.string "Oh? You've too many POKéMON.\n"
	.string "There's no room for this EGG…$"

LilycoveCity_GTS_F2_Text_StartDownloadEgg::
	.string "Do you want to download a gift\n"
	.string "egg?$"

LilycoveCity_GTS_F2_Text_StartDownloadBattle::
	.string "Do you want to start the download\n"
	.string "battle?$"

LilycoveCity_GTS_F2_Text_MailMan::	
	.string "Welcome to the mail service!\p"
	.string "How may I serve you?$"

LilycoveCity_GTS_F2_Text_SelectMailMon::
	.string "Please select a POKéMON whose mail\n"
	.string "you wish to send.$"

LilycoveCity_GTS_F2_Text_MailSent::
	.string "Your mail has been sent!\p"
	.string "Thank you for using the mail service.\n"
	.string "We hope to see you again soon.$"

LilycoveCity_GTS_F2_Text_MonHadNoMail::
    .string "Oh… I'm sorry…\p"
	.string "That POKéMON doesn't appear to be\n" 
	.string "holding any mail...$"

LilycoveCity_GTS_F2_Text_NoMailFound::
	.string "No new mail was found.$"

LilycoveCity_GTS_F2_Text_StartDownloadMart::
	.string "Do you want to start the online mart?$"

LilycoveCity_GTS_F2_EventScript_DontConnect::
	release
	end

