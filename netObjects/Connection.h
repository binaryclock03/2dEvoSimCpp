#pragma once

struct Connection
{
  Connection();
  Connection(int adrA, int adrB, float strength);
  int adrA;
  int adrB;
  float strength;
};