# Žodžių skaičiavymo programa

Ši programa nuskaito toje pačioje direktorijoje esantį failą input_file.txt

Suskaičiuoja kiek skirtingų žodžių yra jame. Galiausiai išveda žodžius kurie tekste pasikartojo daugiau nei vieną kartą į failą output_file.txt.

Taipogi išveda visus rastus url adresus į consolę.

URL adresai randami pagal:
```c++
if (word.find(".") != std::string::npos || word.find("www.") != std::string::npos || word.find("https://") != std::string::npos){
  cout << word << endl;
}
```
