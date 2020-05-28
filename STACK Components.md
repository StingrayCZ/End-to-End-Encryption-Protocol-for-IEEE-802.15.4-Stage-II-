## STCK componets

### Security enable
```sh
#if defined(NWK_ENABLE_SECURITY) && (SYS_SECURITY_MODE == 0)
  #define PHY_ENABLE_AES_MODULE
#endif

#endif // _SYS_CONFIG_H_
```

### Testing ECDH modules (printing random number)

```sh
#ifdef USB_DEBUG
TESTRAND = rand();
printf("\r\nRandom cislo je %d",TESTRAND);
#endif
```

### Testing ECDH modules (printing random number)
