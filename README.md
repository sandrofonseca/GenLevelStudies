# GenLevelStudies

cmsrel CMSSW_10_6_4

cd CMSSW_10_6_4/src/

cmsenv

git clone git@github.com:sandrofonseca/GenLevelStudies.git

mv GenLevelStudies/GenTutorial/ .

rm -r GenLevelStudies

cd GenTutorial/GenLevelStudies

voms-proxy-init --rfc --voms cms

scram b -j8

cmsRun test/genlevel.py
 
 

 
