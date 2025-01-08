1. For now, I let p and q to be 32 bit. Maybe consider using GMP library and make p and q at least 1024 bits.
2. As mentioned by Sam, I may consider implement cpa secure in future.
3. maybe create make file for easier compilation
4. The current implementation works fine in small prime. But if p and q and long plain text are large we encounter overflow issue, so back to point 1.