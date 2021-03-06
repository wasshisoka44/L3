<?xml version='1.0' encoding='utf-8'?>
<xsl:stylesheet version='1.0' xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<xsl:output method='xml' encoding='utf-8' indent='yes'/>

	<xsl:template name='get_journee'>
		<xsl:param name='n'/>
		<xsl:copy-of select='//journees/journee[@num=$n]'/>
	</xsl:template>

	<xsl:template match='/'>
		<xsl:call-template name='get_journee'>
			<xsl:with-param name='n' select='18'/>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>
