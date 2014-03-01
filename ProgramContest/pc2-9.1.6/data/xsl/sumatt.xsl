<!-- $Id: sumatt.xsl 1132 2007-12-01 20:24:52Z boudreat $ -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:output method="html" indent="yes"/>
<xsl:decimal-format decimal-separator="." grouping-separator="," />
<xsl:template match="contestStandings">
    <HTML>
        <HEAD>
<TITLE>
Summary/Attempt - <xsl:value-of select="/contestStandings/standingsHeader/@title"/>
</TITLE>
<META HTTP-EQUIV="EXPIRES" CONTENT="0"/>
<META HTTP-EQUIV="CACHE-CONTROL" CONTENT="NO-CACHE"/>
<META HTTP-EQUIV="PRAGMA" CONTENT="NO-CACHE"/>
        </HEAD>
        <BODY>
            <TABLE border="1">
                <tr>
<th><strong><u>Name</u></strong></th>
                <xsl:call-template name="problemTitle"/>
<th>Total att/solv</th></tr>
<tr>
<td></td>
                <xsl:call-template name="problemColor"/>
</tr>
                <xsl:call-template name="teamStanding"/>
                <xsl:call-template name="summary"/>
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

        <xsl:template name="summary">
            <xsl:for-each select="standingsHeader">
                <tr>
<td>Submitted/1st Yes/Total Yes</td>
                <xsl:call-template name="problemsummary"/>
<td><xsl:value-of select="@totalAttempts"/>/<xsl:value-of select="@totalSolved"/></td>
                </tr>
            </xsl:for-each>
        </xsl:template>
        <xsl:template name="problemsummary">
            <xsl:for-each select="/contestStandings/standingsHeader/problem">
<!-- <problemsummary attempts="246" bestSolutionTime="25" id="1" lastsolutionTime="283" numberSolved="81" title="A+ Consanguine Calculations"/> -->
<td>
<xsl:value-of select="@attempts"/>/<xsl:if test="@numberSolved &lt; 1">--</xsl:if>
<xsl:if test="@bestSolutionTime"><xsl:value-of select="@bestSolutionTime"/></xsl:if>/<xsl:value-of select="@numberSolved"/>
</td>
            </xsl:for-each>
        </xsl:template>
        <xsl:template name="teamStanding">
            <xsl:for-each select="teamStanding">
                <tr>
<!-- <teamStanding index="1" solved="8" problemsattempted="8" rank="1" score="1405" teamName="Warsaw University" timefirstsolved="13" timelastsolved="272" totalAttempts="19" userid="84" usersiteid="1"> -->
<td><xsl:value-of select="@teamName"/></td>
                <xsl:call-template name="problemSummaryInfo"/>
<td><xsl:value-of select="@totalAttempts"/>/<xsl:value-of select="@solved"/></td>
                </tr>
            </xsl:for-each>
        </xsl:template>
        <xsl:template name="problemSummaryInfo">
            <xsl:for-each select="problemSummaryInfo">
<!-- <problemSummaryInfo attempts="1" index="1" problemid="1" score="73" solutionTime="73"/> -->
<td>
<xsl:value-of select="@attempts"/>/<xsl:if test="@isSolved = 'false'">N</xsl:if>
<xsl:if test="@isSolved = 'true'">Y</xsl:if>
</td>
            </xsl:for-each>
        </xsl:template>
        <xsl:template name="problemTitle">
            <xsl:for-each select="/contestStandings/standingsHeader/problem">
<th>&#160;&#160;&#160;&#160;<strong><u><xsl:number format="A" value="@id"/></u></strong>&#160;&#160;&#160;&#160;</th>
            </xsl:for-each>
        </xsl:template>
        <xsl:template name="problemColor">
            <xsl:for-each select="/contestStandings/standingsHeader/colorList/colors[@siteNum = 1]/problem">
                <td><center><xsl:choose><xsl:when test="@color"> <xsl:value-of select="@color"/></xsl:when><xsl:otherwise>Color<xsl:value-of select="@id"/></xsl:otherwise></xsl:choose></center></td>
            </xsl:for-each>
        </xsl:template>
</xsl:stylesheet>
