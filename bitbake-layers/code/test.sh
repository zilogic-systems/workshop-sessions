mkdir -p ~/yp/lunch/meta-burger
mkdir -p ~/yp/lunch/meta-burger/conf

cat > ~/yp/lunch/conf/bblayers.conf <<"EOF"
BBLAYERS = "            \
  ${TOPDIR}/meta        \
  ${TOPDIR}/meta-burger \
"
EOF

cat > ~/yp/lunch/meta-burger/conf/layer.conf <<"EOF"
BBPATH .= ":${LAYERDIR}"

BBFILES += "${LAYERDIR}/*.bb ${LAYERDIR}/*.bbappend"

BBFILE_COLLECTIONS += "burger"
BBFILE_PATTERN_burger := "^${LAYERDIR}/"
EOF

cat > ~/yp/lunch/meta-burger/burger.bb <<"EOF"
PN = "burger"

DEPENDS = "omelet"

do_get() {
        echo ${PN}: bun > burger.txt
        echo ${PN}: cheese >> burger.txt
        cat omelet.txt  >> burger.txt
        sleep 1
}

do_cook() {
        echo "${PN}: toast bread and serve" >> burger.txt
        sleep 2
        echo "${PN}: ready" >> burger.txt
}
EOF

cat > ~/yp/lunch/meta-burger/omelet.bbappend <<"EOF"

do_get() {
        echo ${PN}: less pepper > omelet.txt
        echo ${PN}: egg >> omelet.txt
}
EOF
