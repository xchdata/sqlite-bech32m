LDFLAGS := -fPIC -shared

libbech32m.so: bech32m_ext.c bech32m.c
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ $^

.PHONY: clean
clean:
	$(RM) libbech32m.so
