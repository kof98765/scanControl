#ifndef PARAM_H
#define PARAM_H

#include <QString>

#define ETH_MQ_TX_NONE 0

//static const struct rte_eth_conf port_conf = {
//    rxmode = {
//        split_hdr_size = 0,
//        header_split   = 0,
//        hw_ip_checksum = 0,
//        hw_vlan_filter = 0,
//        jumbo_frame    = 0,
//        hw_strip_crc   = 0,
//    },
//    txmode = {
//        mq_mode = ETH_MQ_TX_NONE,
//    },
//};

struct DATA
{
    QString type;
    int     num;
    int     sum;
    double  area;
    double  width;
    double  length;
};


#endif // PARAM_H
