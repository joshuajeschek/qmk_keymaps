	qmk c2json indil/keymap.c -km indil -kb splitkb/aurora/lily58/rev1 --no-cpp  > export.json
	sed -i 's/"___"/"KC_TRNS"/g' export.json
	sed -i 's/"_x_"/"KC_NO"/g' export.json
	sed -i 's/_DEFAULT/0/g' export.json
	sed -i 's/_LOWER/1/g' export.json
	sed -i 's/_RAISE/2/g' export.json
	sed -i 's/_ADJUST/3/g' export.json
	sed -i 's/_GAMING/4/g' export.json
  sed -i 's/"DYNENT"/"KC_ENT"/g' export.json
  exit
  sed -i 's/"RALT(KC_Q)"/"AT"/g' export.json
  sed -i 's/"RALT(KC_E)"/"ANY(€)"/g' export.json
  sed -i 's/"LBRCK"/"["/g' export.json
  sed -i 's/"RBRCK"/"ANY(])"/g' export.json
  sed -i 's/"GRTR"/"ANY(>)"/g' export.json
  sed -i 's/"LESS"/"ANY(<)"/g' export.json
  sed -i 's/"DLLR"/"ANY($)"/g' export.json
  sed -i 's/"BSLSH"/"ANY(\\\\)"/g' export.json
  sed -i 's/"PERC"/"ANY(%)"/g' export.json
  sed -i 's/"LCURL"/"ANY({)"/g' export.json
  sed -i 's/"RCURL"/"ANY(})"/g' export.json
  sed -i 's/"PIPE"/"ANY(|)"/g' export.json
  sed -i 's/"TILD"/"ANY(~)"/g' export.json
