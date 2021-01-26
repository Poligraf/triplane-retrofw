#!/bin/sh
mkdir -p $HOME/.triplane;

[ ! -f ~/.triplane/triplane.cfg ] && cp ./config/triplane.cfg $HOME/.triplane/triplane.cfg;
[ ! -f ~/.triplane/roster.dta ] && cp ./config/roster.dta $HOME/.triplane/roster.dta;
[ ! -f ~/.triplane/keyset.dta ] && cp ./config/keyset.dta $HOME/.triplane/keyset.dta;

./triplane-classic
