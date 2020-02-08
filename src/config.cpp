#include "config.h"

#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

void readConfig()
{
  ifstream fin("config.txt");

  string t;
  fin >> t >> config.FOV;
  cout << t + ": " << config.FOV << endl;

  fin >> t >> config.viewDistance;
  cout << t + ": " << config.viewDistance << endl;

  fin >> t >> config.mouseSensitivity;
  cout << t + ": " << config.mouseSensitivity << endl;

  fin >> t >> config.runSpeed;
  cout << t + ": " << config.runSpeed << endl;

  fin >> t >> config.playerHeight;
  cout << t + ": " << config.playerHeight << endl;

  fin >> t >> config.jumpPower;
  cout << t + ": " << config.jumpPower << endl;

  fin >> t >> config.skyColour.x >> config.skyColour.y >> config.skyColour.z;
  cout << t + ": " << config.skyColour.x <<  " " <<
    config.skyColour.y << " " << config.skyColour.z << endl;

  fin >> t >> config.bucketSize;
  cout << t + ": " << config.bucketSize << endl;

  fin >> t >> config.bucketVertexCount;
  cout << t + ": " << config.bucketVertexCount << endl;

  fin >> t >> config.bucketMaxHeight;
  cout << t + ": " << config.bucketMaxHeight << endl;

  fin >> t >> config.gravity;
  cout << t + ": " << config.gravity << endl;

  fin.close();
}
