echo "making...."
make -j8
echo "running Neutron HallB, run $1"
rm -fr nDetEffg4_run$1.root 
./nOnScintillator short_run.mac
echo "finished Geant4"
hadd nDetEffg4_run$1.root nOnScintillator_t*.root
rm -fr nOnScintillator*.root
mv nDetEffg4_run$1.root ~/Desktop/Geant4Projects/root_files/
echo "done, see results ar"
echo "~/Desktop/Geant4Projects/nDetEffg4_run$1.root"