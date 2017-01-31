#! /bin/csh -f
./pp1 pp1.mac
root -q -l -b FillTree.C 
root -l Plot.C

