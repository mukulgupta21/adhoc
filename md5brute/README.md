# MD5brute
A simple command line application to brute force all combinations of n-letter passwords
using the password policy of 1 upper-case, 1 lower case, 1 numeric and 1 special character

Usage of this is recommended only for educational purposes. For serious use, consider using
hashcat.

## Dependencies
- Openssl: for MD5 crypto library.

## Usage
Edit `md5.txt` file to match with candidate md5 digests.
```
make
./md5brute
```

## Benchmarks
- 3.5 million MD5 hashes per second.

