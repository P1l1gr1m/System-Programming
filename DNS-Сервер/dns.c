
/************************************************************ *************
LAB 1

Edit this file ONLY!

************************************************************ *************/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h> 
#include "dns.h"
#include "list.h"

Node** DNS_Servers[20] = { 0 };
DNSHandle InitDNS()
{
    int i = 1;
    for (; i < 21; i++)
    {
        if (DNS_Servers[i + 1] == 0)
        {
            Node** Hosts;
            Hosts = (Node**)malloc(1000001 * sizeof(Node*));

            if (Hosts != 0)
            {
                for (int i = 0; i < 1000001; i++)
                {
                    *(Hosts + i) = 0;
                }

                DNS_Servers[i + 1] = Hosts;
                return (DNSHandle)(i + 1);
            }
        }
    }
    return (DNSHandle)0;
}

static unsigned long sdbm(str)
unsigned char* str;
{
    unsigned long hash = 0;
    int c;

    while ((c = *str++))
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

void LoadHostsFile(DNSHandle hDNS, const char* hostsFilePath)
{
    if (DNS_Servers[hDNS] == 0)
        exit(-1);

    FILE* HostsFile;
    char hostName[255];
    char* pHostName = &hostName[0];
    unsigned int IP1, IP2, IP3, IP4, IP;
    unsigned long hash_idx;
    fopen_s(&HostsFile, hostsFilePath, "r");

    if (HostsFile != NULL && hDNS != 0)
    {
        while (fscanf_s(HostsFile, "%d.%d.%d.%d\t%s", &IP1, &IP2, &IP3, &IP4, hostName, _countof(hostName)) != EOF)
        {
            hash_idx = sdbm((unsigned char*)hostName);

            if (hash_idx != 0)
            {
                hash_idx = hash_idx % 1000000 + 1;
                IP = (((((IP1 << 8) + IP2) << 8) + IP3) << 8) + IP4;
                unsigned int HNLength = strlen(hostName);
                char* tmpHostName = 0;

                if (HNLength != 0)
                {
                    tmpHostName = (char*)malloc(HNLength + 1);
                    strcpy(tmpHostName, pHostName);
                    push(DNS_Servers[hDNS] + hash_idx, IP, tmpHostName);
                }

            }
        }

        fclose(HostsFile);
    }
}

IPADDRESS DnsLookUp(DNSHandle hDNS, const char* hostName)
{
    if (DNS_Servers[hDNS] == 0)
        exit(-1);

    unsigned long hash = sdbm((unsigned char*)hostName);

    if (hash != 0 && hDNS != 0)
    {
        hash = hash % 1000000 + 1;
        Node* tmp = *(DNS_Servers[hDNS] + hash);

        while (tmp != NULL)
        {
            if (strcmp(hostName, tmp->HostName) == 0)
                return tmp->IPadress;
            else
                tmp = tmp->next;
        }
    }

    return INVALID_IP_ADDRESS;
}

void ShutdownDNS(DNSHandle hDNS)
{
    if (DNS_Servers[hDNS] != 0)
    {
        Node* tmp = *DNS_Servers[hDNS];

        for (int i = 0; i < 1000001; i++)
        {
            if (tmp != NULL)
                deleteList(&tmp);
            tmp = *(DNS_Servers[hDNS] + i);
        }

        free(DNS_Servers[hDNS]);
        DNS_Servers[hDNS] = 0;
    }
}
