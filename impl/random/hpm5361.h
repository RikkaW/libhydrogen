__attribute__((weak))
void hydro_hpm5361_init_random(void);

__attribute__((weak))
uint32_t hydro_hpm5361_get_random_number(void);

int hydro_random_init(void)
{
    const char       ctx[hydro_hash_CONTEXTBYTES] = { 'h', 'y', 'd', 'r', 'o', 'P', 'R', 'G' };
    hydro_hash_state st;
    uint16_t         ebits = 0;

    hydro_hpm5361_init_random();

    hydro_hash_init(&st, ctx, NULL);

    while (ebits < 256) {
        uint32_t r = hydro_hpm5361_get_random_number();

        hydro_hash_update(&st, (const uint32_t *) &r, sizeof r);
        ebits += 32;
    }

    hydro_hash_final(&st, hydro_random_context.state, sizeof hydro_random_context.state);
    hydro_random_context.counter = ~LOAD64_LE(hydro_random_context.state);

    return 0;
}
