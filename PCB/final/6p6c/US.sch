<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.5.1">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="24" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Yijiano">
<packages>
<package name="6P6C_FEMALE">
<pad name="2" x="0.51" y="1.27" drill="0.9" diameter="1.3"/>
<pad name="5" x="-0.51" y="-1.27" drill="0.9" diameter="1.3"/>
<pad name="6" x="1.53" y="-1.27" drill="0.9" diameter="1.3"/>
<pad name="3" x="2.55" y="1.27" drill="0.9" diameter="1.3"/>
<pad name="1" x="-1.53" y="1.27" drill="0.9" diameter="1.3"/>
<pad name="4" x="-2.55" y="-1.27" drill="0.9" diameter="1.3"/>
<wire x1="6" y1="11.27" x2="-6" y2="11.27" width="0.127" layer="51"/>
<wire x1="-6" y1="11.27" x2="-6" y2="-2.43" width="0.127" layer="51"/>
<wire x1="-6" y1="-2.43" x2="6" y2="-2.43" width="0.127" layer="51"/>
<wire x1="6" y1="-2.43" x2="6" y2="11.27" width="0.127" layer="51"/>
<text x="-2.54" y="12.7" size="1.27" layer="25">&gt;NAME</text>
<text x="-2.54" y="-5.08" size="1.27" layer="27">&gt;VALUE</text>
<hole x="6" y="3.57" drill="2.3"/>
<hole x="-6" y="3.57" drill="2.3"/>
</package>
<package name="SUPERIORSIM">
<pad name="." x="0" y="0" drill="1" diameter="2"/>
<text x="1.27" y="0" size="0.4064" layer="25">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="6P6C_FEMALE">
<pin name="1" x="-2.54" y="6.35" visible="pin" length="short"/>
<pin name="2" x="-2.54" y="3.81" visible="pin" length="short"/>
<pin name="3" x="-2.54" y="1.27" visible="pin" length="short"/>
<pin name="4" x="-2.54" y="-1.27" visible="pin" length="short"/>
<pin name="5" x="-2.54" y="-3.81" visible="pin" length="short"/>
<pin name="6" x="-2.54" y="-6.35" visible="pin" length="short"/>
<wire x1="0" y1="6.35" x2="0" y2="-1.27" width="0.254" layer="94"/>
<text x="-2.54" y="8.89" size="1.778" layer="95">&gt;NAME</text>
<text x="-2.54" y="-11.43" size="1.778" layer="96">&gt;VALUE</text>
<wire x1="0" y1="-1.27" x2="0" y2="-6.35" width="0.254" layer="94"/>
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-1.27" y1="1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="-1.27" x2="1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="1.27" y1="1.27" x2="-1.27" y2="1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="-1.27" width="0.254" layer="94"/>
<rectangle x1="-1.27" y1="-1.27" x2="1.27" y2="1.27" layer="90"/>
</symbol>
<symbol name="PAD">
<text x="-1.143" y="1.8542" size="1.778" layer="95">&gt;NAME</text>
<text x="-1.143" y="-3.302" size="1.778" layer="96">&gt;VALUE</text>
<pin name="P" x="2.54" y="0" visible="off" length="short" direction="pas" rot="R180"/>
<wire x1="0" y1="0" x2="-1" y2="-1" width="0.254" layer="94" curve="-90"/>
<wire x1="-1" y1="-1" x2="0" y2="0" width="0.254" layer="94" curve="-90"/>
<wire x1="1" y1="1" x2="0" y2="0" width="0.254" layer="94" curve="-90"/>
<wire x1="0" y1="0" x2="1" y2="1" width="0.254" layer="94" curve="-90"/>
<wire x1="-1" y1="1" x2="0" y2="0" width="0.254" layer="94" curve="-90"/>
<wire x1="0" y1="0" x2="-1" y2="1" width="0.254" layer="94" curve="-90"/>
<wire x1="1" y1="-1" x2="0" y2="0" width="0.254" layer="94" curve="-90"/>
<wire x1="0" y1="0" x2="1" y2="-1" width="0.254" layer="94" curve="-90"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="6P6C_FEMALE" prefix="C" uservalue="yes">
<gates>
<gate name="G$1" symbol="6P6C_FEMALE" x="-50.8" y="12.7"/>
</gates>
<devices>
<device name="SMD" package="6P6C_FEMALE">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
<connect gate="G$1" pin="3" pad="3"/>
<connect gate="G$1" pin="4" pad="4"/>
<connect gate="G$1" pin="5" pad="5"/>
<connect gate="G$1" pin="6" pad="6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="BETTERPAD_2.54" prefix="PAD">
<gates>
<gate name="P" symbol="PAD" x="0" y="0"/>
</gates>
<devices>
<device name="" package="SUPERIORSIM">
<connects>
<connect gate="P" pin="P" pad="."/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="C1" library="Yijiano" deviceset="6P6C_FEMALE" device="SMD"/>
<part name="PAD1" library="Yijiano" deviceset="BETTERPAD_2.54" device=""/>
<part name="PAD2" library="Yijiano" deviceset="BETTERPAD_2.54" device=""/>
<part name="PAD3" library="Yijiano" deviceset="BETTERPAD_2.54" device=""/>
<part name="PAD4" library="Yijiano" deviceset="BETTERPAD_2.54" device=""/>
<part name="PAD5" library="Yijiano" deviceset="BETTERPAD_2.54" device=""/>
<part name="PAD6" library="Yijiano" deviceset="BETTERPAD_2.54" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="C1" gate="G$1" x="52.07" y="49.53" smashed="yes"/>
<instance part="PAD1" gate="P" x="45.72" y="55.88" smashed="yes"/>
<instance part="PAD2" gate="P" x="45.72" y="53.34" smashed="yes"/>
<instance part="PAD3" gate="P" x="45.72" y="50.8" smashed="yes"/>
<instance part="PAD4" gate="P" x="45.72" y="48.26" smashed="yes"/>
<instance part="PAD5" gate="P" x="45.72" y="45.72" smashed="yes"/>
<instance part="PAD6" gate="P" x="45.72" y="43.18" smashed="yes"/>
</instances>
<busses>
</busses>
<nets>
<net name="N$1" class="0">
<segment>
<pinref part="PAD1" gate="P" pin="P"/>
<pinref part="C1" gate="G$1" pin="1"/>
<wire x1="48.26" y1="55.88" x2="49.53" y2="55.88" width="0.1524" layer="91"/>
<label x="38.1" y="55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$2" class="0">
<segment>
<pinref part="PAD2" gate="P" pin="P"/>
<pinref part="C1" gate="G$1" pin="2"/>
<wire x1="48.26" y1="53.34" x2="49.53" y2="53.34" width="0.1524" layer="91"/>
<label x="38.1" y="53.34" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$3" class="0">
<segment>
<pinref part="PAD3" gate="P" pin="P"/>
<pinref part="C1" gate="G$1" pin="3"/>
<wire x1="48.26" y1="50.8" x2="49.53" y2="50.8" width="0.1524" layer="91"/>
<label x="38.1" y="50.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$4" class="0">
<segment>
<pinref part="PAD4" gate="P" pin="P"/>
<pinref part="C1" gate="G$1" pin="4"/>
<wire x1="48.26" y1="48.26" x2="49.53" y2="48.26" width="0.1524" layer="91"/>
<label x="38.1" y="48.26" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$5" class="0">
<segment>
<pinref part="PAD5" gate="P" pin="P"/>
<pinref part="C1" gate="G$1" pin="5"/>
<wire x1="48.26" y1="45.72" x2="49.53" y2="45.72" width="0.1524" layer="91"/>
<label x="38.1" y="45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="N$6" class="0">
<segment>
<pinref part="PAD6" gate="P" pin="P"/>
<pinref part="C1" gate="G$1" pin="6"/>
<wire x1="48.26" y1="43.18" x2="49.53" y2="43.18" width="0.1524" layer="91"/>
<label x="38.1" y="43.18" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
