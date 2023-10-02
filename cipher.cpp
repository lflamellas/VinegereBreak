// Aluno: Luis Fernando Freitas Lamellas
// Matrícula: 19/0016841

#include <bits/stdc++.h>
using namespace std;

string encryption(string message, string keyword)
{
  string cipher;
  for (int i = 0; i < message.size(); i++)
  {
    if (message[i] < 'A' or message[i] > 'Z')
    {
      cipher.push_back(message[i]);
      continue;
    }
    char letter = (message[i] + keyword[i % keyword.size()]) % 26 + 'A';
    cipher.push_back(letter);
  }
  return cipher;
}

string decryption(string cipher, string keyword)
{
  string message;
  for (int i = 0; i < cipher.size(); i++)
  {
    if (cipher[i] < 'A' or cipher[i] > 'Z')
    {
      message.push_back(cipher[i]);
      continue;
    }
    char letter = (cipher[i] - keyword[i % keyword.size()] + 26) % 26 + 'A';
    message.push_back(letter);
  }
  return message;
}

int main()
{
  string message = "ATTACKATDAWN";
  string keyword = "LEMON";
  string cipher = encryption(message, keyword);
  string original = decryption(cipher, keyword);
  cout << cipher << endl;
  cout << original << endl;
}
