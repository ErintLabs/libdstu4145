/*
* Copyright 2016 Erint Labs OÜ
*
* Licensed under the EUPL, Version 1.1 or – as soon they
* will be approved by the European Commission - subsequent
* versions of the EUPL (the "Licence");
* You may not use this work except in compliance with the
* Licence.
* You may obtain a copy of the Licence at:
*
* https://joinup.ec.europa.eu/software/page/eupl
*
* Unless required by applicable law or agreed to in
* writing, software distributed under the Licence is
* distributed on an "AS IS" basis,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied.
* See the Licence for the specific language governing
* permissions and limitations under the Licence.
*/
#include "legacy.h"

static struct
{
    int *nid;
    const char *on;
    const char *sn;
    const char *ln;
} 
oid_data[] =
{
    /* GOST cipher */
    { &NID-id-Gost28147,                "1.2.804.2.1.1.1.1.1.1",        "Gost28147",                "DSTU GOST 28147:2009 algorithm" },
    { &NID-id-Gost28147ecb,             "1.2.804.2.1.1.1.1.1.1.1",      "Gost28147ecb",             "DSTU GOST 28147:2009 algorithm, ECB mode" },
    { &NID-id-Gost28147ctr,             "1.2.804.2.1.1.1.1.1.1.2",      "Gost28147ctr",             "DSTU GOST 28147:2009 algorithm, CTR mode" },
    { &NID-id-Gost28147cfb,             "1.2.804.2.1.1.1.1.1.1.3",      "Gost28147cfb",             "DSTU GOST 28147:2009 algorithm, CFB mode" },
    { &NID-id-Gost28147cmac,            "1.2.804.2.1.1.1.1.1.1.4",      "Gost28147cmac",            "DSTU GOST 28147:2009 algorithm, CMAC mode" },
    
    /* Kalyna */
    { &NID-id-Dstu7624,                 "1.2.804.2.1.1.1.1.1.2",        "Dstu7624",                 "DSTU 7624:2014 algorithm" },
    { &NID-id-Dstu7624ecb,              "1.2.804.2.1.1.1.1.1.2.1",      "Dstu7624ecb",              "DSTU 7624:2014 algorithm, ECB mode" },
    { &NID-id-Dstu7624ecb_128,          "1.2.804.2.1.1.1.1.1.2.1.1",    "Dstu7624ecb(128)",         "DSTU 7624:2014 algorithm, 128-bit, ECB mode" },
    { &NID-id-Dstu7624ecb_256,          "1.2.804.2.1.1.1.1.1.2.1.2",    "Dstu7624ecb(256)",         "DSTU 7624:2014 algorithm, 256-bit, ECB mode" },
    { &NID-id-Dstu7624ecb_512,          "1.2.804.2.1.1.1.1.1.2.1.3",    "Dstu7624ecb(512)",         "DSTU 7624:2014 algorithm, 512-bit, ECB mode" },
    { &NID-id-Dstu7624ctr,              "1.2.804.2.1.1.1.1.1.2.2",      "Dstu7624ctr",              "DSTU 7624:2014 algorithm, CTR mode" },
    { &NID-id-Dstu7624ctr_128,          "1.2.804.2.1.1.1.1.1.2.2.1",    "Dstu7624ctr(128)",         "DSTU 7624:2014 algorithm, 128-bit, CTR mode" },
    { &NID-id-Dstu7624ctr_256,          "1.2.804.2.1.1.1.1.1.2.2.2",    "Dstu7624ctr(256)",         "DSTU 7624:2014 algorithm, 256-bit, CTR mode" },
    { &NID-id-Dstu7624ctr_512,          "1.2.804.2.1.1.1.1.1.2.2.3",    "Dstu7624ctr(512)",         "DSTU 7624:2014 algorithm, 512-bit, CTR mode" },
    { &NID-id-Dstu7624cfb,              "1.2.804.2.1.1.1.1.1.2.3",      "Dstu7624cfb",              "DSTU 7624:2014 algorithm, CFB mode" },
    { &NID-id-Dstu7624cfb_128,          "1.2.804.2.1.1.1.1.1.2.3.1",    "Dstu7624cfb(128)",         "DSTU 7624:2014 algorithm, 128-bit, CFB mode" },
    { &NID-id-Dstu7624cfb_256,          "1.2.804.2.1.1.1.1.1.2.3.2",    "Dstu7624cfb(256)",         "DSTU 7624:2014 algorithm, 256-bit, CFB mode" },
    { &NID-id-Dstu7624cfb_512,          "1.2.804.2.1.1.1.1.1.2.3.3",    "Dstu7624cfb(512)",         "DSTU 7624:2014 algorithm, 512-bit, CFB mode" },
    { &NID-id-Dstu7624cmac,             "1.2.804.2.1.1.1.1.1.2.4",      "Dstu7624cmac",             "DSTU 7624:2014 algorithm, CMAC mode" },
    { &NID-id-Dstu7624cmac_128,         "1.2.804.2.1.1.1.1.1.2.4.1",    "Dstu7624cmac(128)",        "DSTU 7624:2014 algorithm, 128-bit, CMAC mode" },
    { &NID-id-Dstu7624cmac_256,         "1.2.804.2.1.1.1.1.1.2.4.2",    "Dstu7624cmac(256)",        "DSTU 7624:2014 algorithm, 256-bit, CMAC mode" },
    { &NID-id-Dstu7624cmac_512,         "1.2.804.2.1.1.1.1.1.2.4.3",    "Dstu7624cmac(512)",        "DSTU 7624:2014 algorithm, 512-bit, CMAC mode" },
    { &NID-id-Dstu7624cbc,              "1.2.804.2.1.1.1.1.1.2.5",      "Dstu7624cbc",              "DSTU 7624:2014 algorithm, CBC mode" },
    { &NID-id-Dstu7624cbc_128,          "1.2.804.2.1.1.1.1.1.2.5.1",    "Dstu7624cbc(128)",         "DSTU 7624:2014 algorithm, 128-bit, CBC mode" },
    { &NID-id-Dstu7624cbc_256,          "1.2.804.2.1.1.1.1.1.2.5.2",    "Dstu7624cbc(256)",         "DSTU 7624:2014 algorithm, 256-bit, CBC mode" },
    { &NID-id-Dstu7624cbc_512,          "1.2.804.2.1.1.1.1.1.2.5.3",    "Dstu7624cbc(512)",         "DSTU 7624:2014 algorithm, 512-bit, CBC mode" },
    { &NID-id-Dstu7624ofb,              "1.2.804.2.1.1.1.1.1.2.6",      "Dstu7624ofb",              "DSTU 7624:2014 algorithm, OFB mode" },
    { &NID-id-Dstu7624ofb_128,          "1.2.804.2.1.1.1.1.1.2.6.1",    "Dstu7624ofb(128)",         "DSTU 7624:2014 algorithm, 128-bit, OFB mode" },
    { &NID-id-Dstu7624ofb_256,          "1.2.804.2.1.1.1.1.1.2.6.2",    "Dstu7624ofb(256)",         "DSTU 7624:2014 algorithm, 256-bit, OFB mode" },
    { &NID-id-Dstu7624ofb_512,          "1.2.804.2.1.1.1.1.1.2.6.3",    "Dstu7624ofb(512)",         "DSTU 7624:2014 algorithm, 512-bit, OFB mode" },
    { &NID-id-Dstu7624gmac,             "1.2.804.2.1.1.1.1.1.2.7",      "Dstu7624gmac",             "DSTU 7624:2014 algorithm, GMAC mode" },
    { &NID-id-Dstu7624gmac_128,         "1.2.804.2.1.1.1.1.1.2.7.1",    "Dstu7624gmac(128)",        "DSTU 7624:2014 algorithm, 128-bit, GMAC mode" },
    { &NID-id-Dstu7624gmac_256,         "1.2.804.2.1.1.1.1.1.2.7.2",    "Dstu7624gmac(256)",        "DSTU 7624:2014 algorithm, 256-bit, GMAC mode" },
    { &NID-id-Dstu7624gmac_512,         "1.2.804.2.1.1.1.1.1.2.7.3",    "Dstu7624gmac(512)",        "DSTU 7624:2014 algorithm, 512-bit, GMAC mode" },
    { &NID-id-Dstu7624ccm,              "1.2.804.2.1.1.1.1.1.2.8",      "Dstu7624ccm",              "DSTU 7624:2014 algorithm, CCM mode" },
    { &NID-id-Dstu7624ccm_128,          "1.2.804.2.1.1.1.1.1.2.8.1",    "Dstu7624ccm(128)"          "DSTU 7624:2014 algorithm, 128-bit, CCM mode" },
    { &NID-id-Dstu7624ccm_256,          "1.2.804.2.1.1.1.1.1.2.8.2",    "Dstu7624ccm(256)"          "DSTU 7624:2014 algorithm, 256-bit, CCM mode" },
    { &NID-id-Dstu7624ccm_512,          "1.2.804.2.1.1.1.1.1.2.8.3",    "Dstu7624ccm(512)"          "DSTU 7624:2014 algorithm, 512-bit, CCM mode" },
    { &NID-id-Dstu7624xts,              "1.2.804.2.1.1.1.1.1.2.9",      "Dstu7624xts",              "DSTU 7624:2014 algorithm, XTS mode" },
    { &NID-id-Dstu7624xts_128,          "1.2.804.2.1.1.1.1.1.2.9.1",    "Dstu7624xts(128)",         "DSTU 7624:2014 algorithm, 128-bit, XTS mode" },
    { &NID-id-Dstu7624xts_256,          "1.2.804.2.1.1.1.1.1.2.9.2",    "Dstu7624xts(256)",         "DSTU 7624:2014 algorithm, 256-bit, XTS mode" },
    { &NID-id-Dstu7624xts_512,          "1.2.804.2.1.1.1.1.1.2.9.3",    "Dstu7624xts(512)",         "DSTU 7624:2014 algorithm, 512-bit, XTS mode" },
    { &NID-id-Dstu7624kw,               "1.2.804.2.1.1.1.1.1.2.10",     "Dstu7624kw",               "DSTU 7624:2014 algorithm, KW mode" },
    { &NID-id-Dstu7624kw_128,           "1.2.804.2.1.1.1.1.1.2.10.1",   "Dstu7624kw(128)",          "DSTU 7624:2014 algorithm, 128-bit, KW mode" },
    { &NID-id-Dstu7624kw_256,           "1.2.804.2.1.1.1.1.1.2.10.2",   "Dstu7624kw(256)",          "DSTU 7624:2014 algorithm, 256-bit, KW mode" },
    { &NID-id-Dstu7624kw_512,           "1.2.804.2.1.1.1.1.1.2.10.3",   "Dstu7624kw(512)",          "DSTU 7624:2014 algorithm, 512-bit, KW mode" },
    
    /* GOST hash */
    { &NID-id-Gost34311,                "1.2.804.2.1.1.1.1.2.1",        "Gost34311",                "GOST 34.311-95 hash function" },
    { &NID-id-HmacGost34311,            "1.2.804.2.1.1.1.1.2.3",        "HmacGost34311",            "HMAC algorithm using GOST 34.311-95 hash function" },
    
    /* Kupyna */
    { &NID-id-Dstu7564,                 "1.2.804.2.1.1.1.1.2.2",        "Dstu7564",                 "DSTU 7564:2014 hash function" },
    { &NID-id-Dstu7564_256,             "1.2.804.2.1.1.1.1.2.2.1",      "Dstu7564(256)",            "DSTU 7564:2014 hash function, 256-bit" },
    { &NID-id-Dstu7564_384,             "1.2.804.2.1.1.1.1.2.2.2",      "Dstu7564(384)",            "DSTU 7564:2014 hash function, 384-bit" },
    { &NID-id-Dstu7564_512,             "1.2.804.2.1.1.1.1.2.2.3",      "Dstu7564(512)",            "DSTU 7564:2014 hash function, 512-bit" },
    { &NID-id-Dstu7564mac_256,          "1.2.804.2.1.1.1.1.2.2.4",      "Dstu7564mac(256)",         "DSTU 7564:2014 hash function, 256-bit, MAC mode" },
    { &NID-id-Dstu7564mac_384,          "1.2.804.2.1.1.1.1.2.2.5",      "Dstu7564mac(384)",         "DSTU 7564:2014 hash function, 384-bit, MAC mode" },
    { &NID-id-Dstu7564mac_512,          "1.2.804.2.1.1.1.1.2.2.6",      "Dstu7564mac(512)",         "DSTU 7564:2014 hash function, 512-bit, MAC mode" },
    
    /* DSTU 4145 */
    { &NID-id-Dstu4145WithGost34311,    "1.2.804.2.1.1.1.1.3.1",        "Dstu4145WithGost34311",    "DSTU 4145:2002 signature algorithm with GOST 34.311-95 hash function" },
    { &NID-id-Dstu4145WithDstu7564;     "1.2.804.2.1.1.1.1.3.3",        "Dstu4145WithDstu7564",     "DSTU 4145:2002 signature algorithm with DSTU 7564:2014 hash function" },
    { &NID-id-Dstu4145WithDstu7564_256; "1.2.804.2.1.1.1.1.3.3.1",      "Dstu4145WithDstu7564(256)","DSTU 4145:2002 signature algorithm with DSTU 7564:2014 hash function. 256-bit" },
    { &NID-id-Dstu4145WithDstu7564_384; "1.2.804.2.1.1.1.1.3.3.2",      "Dstu4145WithDstu7564(384)","DSTU 4145:2002 signature algorithm with DSTU 7564:2014 hash function. 384-bit" },
    { &NID-id-Dstu4145WithDstu7564_512; "1.2.804.2.1.1.1.1.3.3.3",      "Dstu4145WithDstu7564(512)","DSTU 4145:2002 signature algorithm with DSTU 7564:2014 hash function. 512-bit" },
     
    /* GOST 34.310 signature */
    { &NID-id-Gost34310WithGost34311,   "1.2.804.2.1.1.1.1.3.2",        "Gost34310WithGost34311",   "GOST 34.310-95 signature algorithm with GOST 34.311-95 hash function" },
    
};
