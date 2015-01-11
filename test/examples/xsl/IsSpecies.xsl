<?xml version="1.0"?>

<xsl:stylesheet  xmlns:functx="http://www.functx.com" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:cml="http://www.xml-cml.org/schema" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xlink="http://www.w3.org/1999/xlink" version="2.0">
	<xsl:output method="text" encoding="UTF-8" indent="yes"/>
	<xsl:strip-space elements="*"/>
    <xsl:param name="elements-of-interest" as="xs:string*" select="C,H"/>
    
<xsl:function name="functx:is-value-in-sequence" as="xs:boolean" 
              xmlns:functx="http://www.functx.com" >
  <xsl:param name="value" as="xs:anyAtomicType?"/> 
  <xsl:param name="seq" as="xs:anyAtomicType*"/> 
 
  <xsl:sequence select=" 
   $value = $seq
 "/>
   
</xsl:function>

<xsl:template match="/">
    <xsl:variable name="element-array" select="tokenize(translate($elements-of-interest,' ',''), ',')"/>
      <xsl:variable name="hits"  as="xs:boolean*">
      <xsl:for-each select="./cml:cml/cml:molecule/cml:molecule/cml:atomArray/cml:atom">
        <xsl:choose>
            <xsl:when test="functx:is-value-in-sequence(@elementType, $element-array)">
                <xsl:value-of select="true()"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="false()"/>
            </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>
      </xsl:variable>
      <!--xsl:value-of select="count($elements-of-interest)"/-->
      <!--xsl:value-of select="$hits"/-->
      <!--xsl:value-of select="string('\n')"/-->
      <xsl:value-of select="not(functx:is-value-in-sequence(false(), $hits))"/>
</xsl:template>

</xsl:stylesheet>