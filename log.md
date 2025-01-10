1. For now, I let p and q to be 32 bit. Maybe consider using GMP library and make p and q at least 1024 bits. fixed
2. As mentioned by Sam, I may consider implement cpa secure in future. Todo
3. maybe create make file for easier compilation Todo
4. The current implementation(see RSA_in_C) works fine in small prime. But if p and q and long plain text are large we encounter overflow issue, so back to point 1. fixed

5. something wrong with the randomness of the prime, and p always equal to q. fixed

6. Maybe get some memory issue so that I can't print anything out while I get into encryption. fixed: at least for text wil a few sentences.
