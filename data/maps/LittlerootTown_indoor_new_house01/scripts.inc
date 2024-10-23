# 1 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"

# 2 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
LittlerootTown_indoor_new_house01_MapScripts::
# 3 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.byte 0

ROUTE101_GIVELEGEND::
# 6 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	lock
# 7 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	faceplayer
# 9 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	goto_if_unset FLAG_ROUTE101GIVEMON, ROUTE101_GIVELEGEND_2
# 41 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox ROUTE101_GIVELEGEND_Text_4
ROUTE101_GIVELEGEND_1:
# 46 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	release
	end

ROUTE101_GIVELEGEND_2:
# 11 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox ROUTE101_GIVELEGEND_Text_0, MSGBOX_YESNO
# 12 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq ROUTE101_GIVELEGEND_5
# 34 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox ROUTE101_GIVELEGEND_Text_3
	goto ROUTE101_GIVELEGEND_1

ROUTE101_GIVELEGEND_5:
# 15 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	checkitem ITEM_BOTTLE_CAP
# 16 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	compare VAR_RESULT, TRUE
	goto_if_eq ROUTE101_GIVELEGEND_8
# 23 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox ROUTE101_GIVELEGEND_Text_2
	goto ROUTE101_GIVELEGEND_1

ROUTE101_GIVELEGEND_8:
# 17 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	setflag FLAG_ROUTE101GIVEMON
# 18 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	removeitem ITEM_BOTTLE_CAP
# 19 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox ROUTE101_GIVELEGEND_Text_1
	goto ROUTE101_GIVELEGEND_1


KANTO_STARTER_CHARMANDER::
# 51 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	lock
# 52 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	faceplayer
# 53 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	goto_if_set FLAG_ROUTE101GIVEMON, KANTO_STARTER_CHARMANDER_2
# 76 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	playmoncry SPECIES_CHARMANDER, CRY_MODE_NORMAL
# 77 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	showmonpic SPECIES_CHARMANDER, 10, 3
# 78 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_CHARMANDER_Text_3
# 79 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	hidemonpic
KANTO_STARTER_CHARMANDER_1:
# 85 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	release
	end

KANTO_STARTER_CHARMANDER_2:
# 54 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_CHARMANDER_Text_0, MSGBOX_YESNO
# 55 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq KANTO_STARTER_CHARMANDER_5
# 66 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_CHARMANDER_Text_2
	goto KANTO_STARTER_CHARMANDER_1

KANTO_STARTER_CHARMANDER_5:
# 56 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_CHARMANDER_Text_1
# 57 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	givemon SPECIES_CHARMANDER, 3, ITEM_DREAM_BALL
# 58 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	setflag FLAG_HAS_KANTO
# 59 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	removeobject 1
	goto KANTO_STARTER_CHARMANDER_1


HiddenItem_LittleRoot::
# 90 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	lock
# 91 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	giveitem ITEM_BOTTLE_CAP, 1
# 92 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	setflag FLAG_HIDDENITEM_LITTLEROOT1
# 93 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	release
	end


KANTO_STARTER_BULBASAUR::
# 99 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	lock
# 100 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	faceplayer
# 101 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	goto_if_set FLAG_ROUTE101GIVEMON, KANTO_STARTER_BULBASAUR_2
# 124 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	playmoncry SPECIES_BULBASAUR, CRY_MODE_NORMAL
# 125 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	showmonpic SPECIES_BULBASAUR, 10, 3
# 126 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_BULBASAUR_Text_2
# 127 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	hidemonpic
KANTO_STARTER_BULBASAUR_1:
# 133 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	release
	end

KANTO_STARTER_BULBASAUR_2:
# 102 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_BULBASAUR_Text_0, MSGBOX_YESNO
# 103 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq KANTO_STARTER_BULBASAUR_5
# 114 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_CHARMANDER_Text_2
	goto KANTO_STARTER_BULBASAUR_1

KANTO_STARTER_BULBASAUR_5:
# 104 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_BULBASAUR_Text_1
# 105 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	givemon SPECIES_BULBASAUR, 3, ITEM_DREAM_BALL
# 106 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	setflag FLAG_HAS_KANTO
# 107 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	removeobject 3
	goto KANTO_STARTER_BULBASAUR_1


KANTO_STARTER_SQUIRTLE::
# 139 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	lock
# 140 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	faceplayer
# 141 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	goto_if_set FLAG_ROUTE101GIVEMON, KANTO_STARTER_SQUIRTLE_2
# 167 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
# 168 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	showmonpic SPECIES_SQUIRTLE, 10, 3
# 169 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_SQUIRTLE_Text_2
# 170 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	hidemonpic
KANTO_STARTER_SQUIRTLE_1:
# 176 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	release
	end

KANTO_STARTER_SQUIRTLE_2:
# 142 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	playmoncry SPECIES_SQUIRTLE, CRY_MODE_NORMAL
# 143 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	showmonpic SPECIES_SQUIRTLE, 10, 3
# 144 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_SQUIRTLE_Text_0, MSGBOX_YESNO
# 145 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	hidemonpic
# 146 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq KANTO_STARTER_SQUIRTLE_5
# 157 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_CHARMANDER_Text_2
	goto KANTO_STARTER_SQUIRTLE_1

KANTO_STARTER_SQUIRTLE_5:
# 147 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	msgbox KANTO_STARTER_SQUIRTLE_Text_1
# 148 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	givemon SPECIES_SQUIRTLE, 3, ITEM_DREAM_BALL
# 149 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	setflag FLAG_HAS_KANTO
# 150 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	removeobject 2
	goto KANTO_STARTER_SQUIRTLE_1


ROUTE101_GIVELEGEND_Text_0:
# 11 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Do you have a Bottle Cap? Ill give you a\n"
	.string "Kanto Pokemon for one.$"

ROUTE101_GIVELEGEND_Text_1:
# 19 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Here you go, as promised you may choose\n"
	.string "one of these three.$"

ROUTE101_GIVELEGEND_Text_2:
# 23 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Hmm.. I don't see one. You could find one\n"
	.string "north of Oldsdale$"

ROUTE101_GIVELEGEND_Text_3:
# 34 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Darn, oh well I heard there is a guy\n"
	.string "north of Oldsdale that is giving them\l"
	.string "away!$"

ROUTE101_GIVELEGEND_Text_4:
# 41 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Hey how have you been?$"

KANTO_STARTER_CHARMANDER_Text_0:
# 54 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Would you like to pick Charmander?$"

KANTO_STARTER_CHARMANDER_Text_1:
# 56 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Okay Charmander will join your team$"

KANTO_STARTER_CHARMANDER_Text_2:
# 66 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "I think I will choose something else$"

KANTO_STARTER_CHARMANDER_Text_3:
# 78 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "CHAR!$"

KANTO_STARTER_BULBASAUR_Text_0:
# 102 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Would you like to pick BULBASAUR?$"

KANTO_STARTER_BULBASAUR_Text_1:
# 104 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Okay BULBASAUR will join your team$"

KANTO_STARTER_BULBASAUR_Text_2:
# 126 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "BULBA!$"

KANTO_STARTER_SQUIRTLE_Text_0:
# 144 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Would you like to pick SQUIRTLE?$"

KANTO_STARTER_SQUIRTLE_Text_1:
# 147 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "Okay SQUIRTLE will join your team$"

KANTO_STARTER_SQUIRTLE_Text_2:
# 169 "data/maps/LittlerootTown_indoor_new_house01/scripts.pory"
	.string "SQUIRTLE!$"
