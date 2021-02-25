#ifndef QMDRLSITEM_H
#define QMDRLSITEM_H

struct RlsItem {
//    <P name='URL'><![CDATA[55/303355.html]]></P>
    QString URL;
//    <P name='TRADENAMEID'><![CDATA[371]]></P>
    QString TRADENAMEID;
//    <P name='TRADENAME'><![CDATA[Аскорбиновая кислота]]></P>
    QString TRADENAME;
//    <P name='NAME'><![CDATA[Аскорбиновая кислота, табл. 50 мг, уп. контурн. яч., 10, пач. картон. 2]]></P>
    QString NAME;
//    <P name='LATNAME'><![CDATA[Ascorbic acid]]></P>
    QString LATNAME;
//    <P name='DRUGFORM_SHORTNAME'><![CDATA[табл.]]></P>
    QString DRUGFORM_SHORTNAME;
//    <P name='DRUGFORM_FULLNAME'><![CDATA[таблетки]]></P>
    QString DRUGFORM_FULLNAME;
//    <P name='GROUP_DRUGFORM'><![CDATA[табл.]]></P>
    QString GROUP_DRUGFORM;
//    <P name='DFMASS'><![CDATA[50]]></P>
    QString DFMASS;
//    <P name='DFMASS_SHORTNAME'><![CDATA[мг]]></P>
    QString DFMASS_SHORTNAME;
//    <P name='DFMASS_FULLNAME'><![CDATA[миллиграмм]]></P>
    QString DFMASS_FULLNAME;
//    <P name='PPACK_SHORTNAME'><![CDATA[уп. контурн. яч.]]></P>
    QString PPACK_SHORTNAME;
//    <P name='PPACK_FULLNAME'><![CDATA[упаковка контурная ячейковая]]></P>
    QString PPACK_FULLNAME;
//    <P name='DRUGSINPPACK'><![CDATA[10]]></P>
    QString DRUGSINPPACK;
//    <P name='UPACK_SHORTNAME'><![CDATA[пач. картон.]]></P>
    QString UPACK_SHORTNAME;
//    <P name='UPACK_FULLNAME'><![CDATA[пачка картонная]]></P>
    QString UPACK_FULLNAME;
//    <P name='PPACKINUPACK'><![CDATA[2]]></P>
    QString PPACKINUPACK;
//    <P name='FIRM_MANUFACTOR'><![CDATA[Биосинтез]]></P>
    QString FIRM_MANUFACTOR;
//    <P name='COUNTRY_MANUFACTOR'><![CDATA[Россия]]></P>
    QString COUNTRY_MANUFACTOR;
//    <P name='FIRM_REGISTRATOR'><![CDATA[Биосинтез]]></P>
    QString FIRM_REGISTRATOR;
//    <P name='JNVLS'><![CDATA[1]]></P>
    QString COUNTRY_REGISTRATOR;
//    <P name='REGNUM'><![CDATA[ЛС-001929]]></P>
    QString REGNUM;
//    <P name='REGDATE'><![CDATA[20110722]]></P>
    QString REGDATE;
//    <P name='REGCERTID'><![CDATA[ЛС-001929-220711]]></P>
    QString REGCERTID;
//    <P name='STATUS'><![CDATA[1]]></P>
    QString STATUS;
//    <P name='NORECIPE'><![CDATA[1]]></P>
    QString NORECIPE;
//    <P name='JNVLS'><![CDATA[1]]></P>
    quint8 JNVLS;
//    <P name='TFR'><![CDATA[1]]></P>
    QString TFR;
//    <P name='NDV'><![CDATA[Аскорбиновая кислота* (Ascorbic acid*)]]></P>
    QString NDV;
//    <P name='OKDP'><![CDATA[2423251,2423501,2423502,2423511,2423512,2423513,2423519,2423521,2423529,2423531,2423539,2423571]]></P>
    QString OKDP;
//    <P name='PHARMGROUP'><![CDATA[198]]></P>
    QString PHARMGROUP;
//    <P name='ATC'><![CDATA[262]]></P>
    QString ATC;
//    <P name='DRUGLIFETIME'><![CDATA[36]]></P>
    QString DRUGLIFETIME;
//    <P name='PHARMAACTIONS'><![CDATA[4, 66, 27, 722]]></P>
    QString PHARMAACTIONS;

    double regPrice;
};

#endif // QMDRLSITEM_H
