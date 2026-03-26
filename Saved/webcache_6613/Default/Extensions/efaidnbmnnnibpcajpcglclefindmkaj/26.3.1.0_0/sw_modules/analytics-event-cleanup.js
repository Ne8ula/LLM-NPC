/*************************************************************************
* ADOBE CONFIDENTIAL
* ___________________
*
*  Copyright 2015 Adobe Systems Incorporated
*  All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Adobe Systems Incorporated and its suppliers,
* if any.  The intellectual and technical concepts contained
* herein are proprietary to Adobe Systems Incorporated and its
* suppliers and are protected by all applicable intellectual property laws,
* including trade secret and or copyright laws.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Adobe Systems Incorporated.
**************************************************************************/
import{dcLocalStorage as e}from"../common/local-storage.js";import{removeExperimentCodeForAnalytics as t}from"../common/experimentUtils.js";import{floodgate as o}from"./floodgate.js";import{cleanupOldPdfRenderingTrackingStorage as r}from"../common/pdf-rendering-tracking.js";const s=["DCBrowserExt:OneNote:Visited","DCBrowserExt:DocsGoogle:Visited:Document","DCBrowserExt:DocsGoogle:Visited:Spreadsheet","DCBrowserExt:DocsGoogle:Visited:Presentation","DCBrowserExt:Gdrive:Image:Opened","DCBrowserExt:Gmail:Image","DCBrowserExt:Gmail:ImageAttachment:Opened"],a=["GDTT","GDTF","GDCF","OT","OTC","EMP","LI","LIC","LC","LCC","LFP","LFF","LFC","GIT","GIC","GIDN"],i=async()=>{((t=[])=>{Array.isArray(t)&&0!==t.length&&t.forEach(t=>{e.getItem(t)&&e.removeItem(t)})})(s),((e=[])=>{Array.isArray(e)&&0!==e.length&&e.forEach(e=>{t(e)})})(a),(async()=>{try{const t=e.getAllItems(),r=[];Object.keys(t).forEach(t=>{const s=t.match(/^DCBrowserExt:([^:]+):Visited$/);if(s&&s.length>1){const a=`dc-cv-${s[1].toLowerCase()}-analytics-visited`;r.push((async()=>{await o.hasFlag(a)||await e.removeItem(t)})())}}),await Promise.all(r)}catch(e){}})(),r()};export{i as clearEventsFromLocalStorage};