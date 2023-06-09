/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2011-2014 Autronica Fire and Security AS
 *
 *	2011-2014 Arvid Brodin, arvid.brodin@alten.se
 */

#ifndef __HSR_PRP_SLAVE_H
#define __HSR_PRP_SLAVE_H

#include <linux/skbuff.h>
#include <linux/netdevice.h>
#include <linux/rtnetlink.h>
#include "hsr_prp_main.h"

int hsr_prp_add_port(struct hsr_prp_priv *hsr, struct net_device *dev,
		     enum hsr_prp_port_type pt);
void hsr_prp_del_port(struct hsr_prp_port *port);
bool hsr_prp_port_exists(const struct net_device *dev);

static inline
struct hsr_prp_port *hsr_prp_port_get_rtnl(const struct net_device *dev)
{
	ASSERT_RTNL();
	return hsr_prp_port_exists(dev) ?
				   rtnl_dereference(dev->rx_handler_data) :
				   NULL;
}

static inline
struct hsr_prp_port *hsr_prp_port_get_rcu(const struct net_device *dev)
{
	return hsr_prp_port_exists(dev) ?
				   rcu_dereference(dev->rx_handler_data) :
				   NULL;
}

#endif /* __HSR_PRP_SLAVE_H */
