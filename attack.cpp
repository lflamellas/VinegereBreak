// Aluno: Luis Fernando Freitas Lamellas
// Matrícula: 19/0016841

#include <bits/stdc++.h>
using namespace std;

int guess_key_size(string cipher)
{
  double min_diff = 999.0;
  vector<tuple<double, int>> matches;
  matches.push_back(make_pair(0.0, 0));
  int key_len = 0;
  for (int displacement = 1; displacement < 11; displacement++)
  {
    int match = 0;
    for (int i = 0; i < cipher.size(); i++)
    {
      if (cipher.size() <= i + displacement)
        break;
      if (cipher[i] == cipher[i + displacement])
        match++;
    }
    double prob = (match * (match - 1) * 1.0) / (cipher.size() * (cipher.size() - 1));
    // cout << displacement << " " << prob << endl;
    matches.push_back(make_pair(prob, displacement));
  }
  sort(matches.begin(), matches.end(), greater());
  // cout << get<1>(matches[0]) << endl;
  return get<1>(matches[0]);
}

double english[26] = {0.08167, 0.01492, 0.02782, 0.04253,
                      0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153,
                      0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929,
                      0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978,
                      0.02360, 0.00150, 0.01974, 0.00074};

double portuguese[26] = {0.1463, 0.0104, 0.0388, 0.0499,
                         0.1257, 0.0102, 0.0130, 0.0128, 0.0618, 0.0040,
                         0.0002, 0.0278, 0.0474, 0.0505, 0.1073, 0.0252,
                         0.0120, 0.0653, 0.0781, 0.0434, 0.0463, 0.0167,
                         0.0001, 0.0021, 0.0001, 0.0047};

string getKeyword(string cipher, int mode = 1)
{
  int keyLength = guess_key_size(cipher);
  string key;
  for (int i = 0; i < keyLength; i++)
  {
    double cipher_probs[26] = {0};
    for (int idx = i; idx < cipher.size(); idx += keyLength)
      cipher_probs[cipher[idx] - 'A']++;
    for (int idx = 0; idx < 26; idx++)
    {
      cipher_probs[idx] *= (double)keyLength / (double)cipher.size();
      // cout << idx << " " << cipher_probs[idx] << endl;
    }

    vector<tuple<int, double>> shifts;
    for (int j = 0; j < 26; j++)
    {
      double chance = 0;
      for (int k = 0; k < 26; k++)
        if (mode == 1)
          chance += (english[k] - cipher_probs[(j + k) % 26]) / english[k];
        else
          chance += (portuguese[k] - cipher_probs[(j + k) % 26]) / portuguese[k];
      shifts.push_back(make_pair(j, chance));
    }
    double proximity = get<1>(shifts[0]);
    int shift = 0;
    for (int j = 0; j < 26; j++)
    {
      if (proximity < get<1>(shifts[j]))
      {
        proximity = get<1>(shifts[j]);
        shift = j;
      }
    }
    key.push_back((char)(shift + 'A'));
  }
  return key;
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
  string cipher1 = "PZEPHCIZYOYMBAPGIDLZMQEMAOCTRQOHGSDAXLYAIVUWKLCFHKZZDZCFZWYOAQOTTZZELWOWDTSMKWVZTFCMIWTLHGSMWWGKCCEETVVUDBQTBKVKDGSMWMEASSDBHOTSCHUWKLCFLVLBAMTWFIPAMACFSYPMIPKEWOAXRCPKJFAZBAKFVZJRHZFSCGNWETGSVIPAKMISGRSQFIUEPBTXNTCLXJPIGLRMHVJJNBVZTMOMVQFWICYWMZCAHSEPXQUKJSTVMPGZDDPBAIVBPBPIIXTWRWLBXAVZTWCIMBKLJRPIGLVZPHEPXQTSRVTMOMOWCHDAIMCCUCCBAMOKTZGMLACVAMEPXQTKIFLBXOAAHTLZEMUKTTQMVBKNTHSIGRQJSOYAPPKUWQLCLMUEDFPWYRCFTGCMIWTLHHZJNTNQWSCQGBQSEFZUHBKGC";
  string cipher2 =
      "VKEMVXFKMISMGYDEYQFGOTCMIIRWYIEGDIYRGTISOMBHGMEJJZZEUIDRJAFSSYEHJLVKOXRPNMHTXSGWDBBTXMEGDXNPZVRRNNBVSEIHVLBWJIWSMUNUAIRTZVNWGULIGMFEAXFVDHNHUWGSNANQISDTMMRRJPFWDAFSGPTEIIQSGXIEQAQIGPXSMQGQUWVGCIIIYSEHZIZITWRKZUBVOKZRVTRQHEIEGPNHGHVQVVRMXETSHXYIDEKSMVNRJSJIDTRKBICTVZNUAECUPMETKWJSVARQGGYEQMQIJIJGMQCXUKIEAQNEJIHYVLNGUQRGMMFGKRKIVUREGHVGDJRVGXRUPMFIGGFRNBNRZIKVJKNHKMEJJZZEKWJIIAIIOWFRGQAIGGIMKBBKXEWMVLRWKQGIIPNYSTRTZTPVAGZEGVNKGVRROQNHGGFRAQQITGZEGQQEJIVMIBRKXMUEYMQSYHRHJAPSTXIMWCVRJSGEMINWKKLVVVNHKXIEIANIYJZRVVPIOVRWXWZYTMTEZACIYWFEDAREZQVWHWQEJSJKJDRVTEDIIBNMY";

  string key = getKeyword(cipher1);
  cout << key << endl;
  string original = decryption(cipher1, getKeyword(cipher1));
  cout << original << endl;

  cout << endl;

  key = getKeyword(cipher2);
  cout << key << endl;
  original = decryption(cipher2, getKeyword(cipher2));
  cout << original << endl;
}
