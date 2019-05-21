#!/bin/bash

TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
SRCDIR=${SRCDIR:-$TOPDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

TITLED=${TITLED:-$SRCDIR/titled}
TITLECLI=${TITLECLI:-$SRCDIR/title-cli}
TITLETX=${TITLETX:-$SRCDIR/title-tx}
TITLEQT=${TITLEQT:-$SRCDIR/qt/title-qt}

[ ! -x $TITLED ] && echo "$TITLED not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTCVER=($($TITLECLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for titled if --version-string is not set,
# but has different outcomes for title_qt and title-cli.
echo "[COPYRIGHT]" > footer.h2m
$TITLED --version | sed -n '1!p' >> footer.h2m

for cmd in $TITLED $TITLECLI $TITLETX $TITLEQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTCVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTCVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
