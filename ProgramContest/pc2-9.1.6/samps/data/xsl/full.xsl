<!-- $Id: full.xsl 1109 2007-11-28 21:45:28Z boudreat $ -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"/>
<xsl:decimal-format decimal-separator="." grouping-separator="," />
<xsl:template match="contestStandings">
    <HTML>
        <HEAD>
<TITLE>
Full Info - <xsl:value-of select="/contestStandings/standingsHeader/@title"/>
</TITLE>
<META HTTP-EQUIV="EXPIRES" CONTENT="0"/>
<META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE"/>
<META HTTP-EQUIV="PRAGMA" CONTENT="NO-CACHE"/>
        </HEAD>
        <BODY>
            <TABLE border="0">
                <tr><th><strong><u>Rank</u></strong></th><th><strong><u>Name</u></strong></th><th><strong><u>Solved</u></strong></th><th><strong><u>Time</u></strong></th></tr>
                <xsl:call-template name="teamStanding"/>
            </TABLE>
<p>
Created by <A HREF="http://www.ecs.csus.edu/pc2">CSUS PC^2 <xsl:value-of select="/contestStandings/standingsHeader/@systemVersion"/></A><br/>
<A HREF="http://www.ecs.csus.edu/pc2/">http://www.ecs.csus.edu/pc2/</A><br/>
Last updated
<xsl:value-of select="/contestStandings/standingsHeader/@currentDate"/>
</p>
        </BODY>
    </HTML>
</xsl:template>

        <xsl:template name="teamStanding">
            <xsl:for-each select="teamStanding">
                <tr>
<td><xsl:value-of select="@rank"/></td>
<td><xsl:value-of select="@teamName"/></td>
<td align="center"><xsl:value-of select="@solved"/></td>
<td align="right"><xsl:value-of select="@points"/></td>
                </tr>
            </xsl:for-each>
        </xsl:template>
</xsl:stylesheet>
