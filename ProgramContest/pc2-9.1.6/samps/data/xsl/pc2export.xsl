<!-- $Id: pc2export.xsl 1072 2007-11-15 18:30:19Z boudreat $ -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="text" indent="yes"/>
<xsl:decimal-format decimal-separator="." grouping-separator="," />
<xsl:template match="contestStandings">
    <xsl:call-template name="exportStanding"/>
</xsl:template>

<xsl:template name="exportStanding">
     <xsl:for-each select="teamStanding">
<xsl:value-of select="@teamExternalId"/>,<xsl:value-of select="@rank"/>,<xsl:value-of select="@solved"/>,<xsl:value-of select="format-number(@points,'0.0')"/>,<xsl:value-of select="format-number(@lastSolved,'0.0')"/>
<xsl:text>
</xsl:text>
     </xsl:for-each>
</xsl:template>
</xsl:stylesheet>
