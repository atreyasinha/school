cmd_/home/atreya/Desktop/school/csci340/kernel-assignment/helloworld/Module.symvers := sed 's/ko$$/o/' /home/atreya/Desktop/school/csci340/kernel-assignment/helloworld/modules.order | scripts/mod/modpost -m -a   -o /home/atreya/Desktop/school/csci340/kernel-assignment/helloworld/Module.symvers -e -i Module.symvers   -T -
