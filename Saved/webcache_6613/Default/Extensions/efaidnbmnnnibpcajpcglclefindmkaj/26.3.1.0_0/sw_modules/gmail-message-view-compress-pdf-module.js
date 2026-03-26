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
import{floodgate as e}from"./floodgate.js";import{setExperimentCodeForAnalytics as o,removeExperimentCodeForAnalytics as s}from"../common/experimentUtils.js";import{checkUserLocaleEnabled as t,safeParseFeatureFlag as i}from"./gsuite/util.js";import{util as a}from"./util.js";async function n(n){const[c,l]=await Promise.all([e.hasFlag("dc-cv-gmail-message-view-compress-pdf-touch-point"),e.hasFlag("dc-cv-gmail-message-view-compress-pdf-touch-point-control")]);let r;c?r=i("dc-cv-gmail-message-view-compress-pdf-touch-point"):l&&(r=i("dc-cv-gmail-message-view-compress-pdf-touch-point-control"));const m=t(r?.enLocaleEnabled,r?.nonEnLocaleEnabled);c&&m?(s("GMCC"),o("GMC")):l&&m?(s("GMC"),o("GMCC")):(s("GMC"),s("GMCC"));const p=r?.messageViewSelectors||{},g=r?.tooltip||{},d=r?.fteEnabled||!1,h=!a.isAcrobatTouchPointEnabled("acrobat-touch-point-in-gmail");n({enableGmailMessageViewCompressPDFTouchPoint:c&&!h&&m,messageViewSelectors:p,compressPDFSizeThreshold:r?.compressPDFSizeThreshold||0,compressPDFString:a.getTranslation("gmailCompressPDFTouchPoint"),fteToolTipStrings:{title:a.getTranslation("gmailCompressPDFTouchPointFTEHeader"),description:a.getTranslation("gmailMessageViewCompressPDFTouchPointFteDescription"),button:a.getTranslation("closeButton")},enableFte:d,fteConfig:g})}export{n as gmailMessageViewCompressPDFInit};