#ifndef _BISMARK_PASSIVE_MAC_TABLE_
#define _BISMARK_PASSIVE_MAC_TABLE_

#include <stdint.h>
#include <stdio.h>
#include <zlib.h>
#include <net/ethernet.h>

#include "constants.h"

/* A list of MAC addresses. A MAC address ID is simply
 * that MAC's index offset into this array. */
typedef struct {
  uint8_t entries[MAC_TABLE_ENTRIES][ETH_ALEN];
  /* The index of the first (i.e., oldest) MAC address in the list */
  int first;
  /* The index of the last (i.e., newest) MAC address in the list */
  int last;
  int length;
  /* The index of the last MAC address sent to the server. */
  int added_since_last_update;
} mac_table_t;

void mac_table_init(mac_table_t* const table);

/* Add a new address to the MAC table. If the table if full, then the oldest
 * address will be discarded to make room. */
int mac_table_lookup(mac_table_t* const table, const uint8_t mac[ETH_ALEN]);

/* Serialize all MAC addresses in the table to a file. */
int mac_table_write_update(mac_table_t* const table, gzFile handle);

#endif
