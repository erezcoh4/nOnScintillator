echo "making...."
make -j8
echo "running Neutron HallB, run $1"
rm -fr BANDgeant4_run$1.root 
./NeutronHallB long_run.mac
echo "finished Geant4"
hadd BANDgeant4_run$1.root NeutronHallB_t*.root
rm -fr NeutronHallB*.root
mv BANDgeant4_run$1.root ~/Desktop/NeutronHallB/G4_root_files/
echo "done, see results ar"
echo "~/Desktop/NeutronHallB/G4_root_files/BANDgeant4_run$1.root"