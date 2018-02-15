# qthessian
Qt implementation of the hessian protocol

# Preparation 

Get a local copy of the qhessian repository with command

git clone https://github.com/hoangtuanbs/qthessian.git
Add include macro into your source file line

#include "{$path}/QtHessian.h"

# Usage

Create a network manager connection:

networkManager = new HNetworkManager("http://localhost:8080/TestService/Test");

Execute a RPC with:

HCall c (networkManager, "feedback");

Insert arguments with:

 c<<"data";
 
And execute remote call with:

c.getResult()
