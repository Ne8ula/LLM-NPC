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
import{floodgate as t}from"./floodgate.js";import{dcLocalStorage as e}from"../common/local-storage.js";import{fetchDefaultViewershipConfig as i}from"../content_scripts/utils/util.js";import{setExperimentCodeForAnalytics as a,removeExperimentCodeForAnalytics as r}from"../common/experimentUtils.js";import{util as o}from"./util.js";const l=e=>{try{return JSON.parse(t.getFeatureMeta(e))}catch(t){return{}}},s=(t,e)=>({gdrive:{treatment:"GDIT",control:"GDIC"}}[t]?.[e]||"");async function n(n,c){const[m,p]=await Promise.all([t.hasFlag(`dc-cv-${n}-implicit-default-viewership`),t.hasFlag(`dc-cv-${n}-implicit-default-viewership-control`)]);if(!m&&!p)return void c({enableImplicitDefaultViewershipFeature:!1,isAcrobatDefaultForSurface:!1,toastMessage:"",fteToolTipStrings:{title:"",description:"",button:""}});let u={};m?u=l(`dc-cv-${n}-implicit-default-viewership`):p&&(u=l(`dc-cv-${n}-implicit-default-viewership-control`));const f=((t,i)=>{const a="en-US"===e.getItem("locale")||"en-GB"===e.getItem("locale");return a&&t||!a&&i})(!!u&&u.enLocaleEnabled,!!u&&u.nonEnLocaleEnabled),d=e.getItem(`${n}-pdf-default-viewership`),g=e.getItem("pdfViewer");""===d&&"false"!==g&&f&&(m?(e.setItem(`${n}-pdf-implicit-dv-feature-enablement-status`,"true"),e.setItem(`${n}-pdf-default-viewership`,"true")):p&&e.setItem(`${n}-pdf-implicit-dv-feature-enablement-status`,"false"));const v=s(n,"treatment"),I=s(n,"control"),$=e.getItem(`${n}-pdf-implicit-dv-feature-enablement-status`);"true"===$&&f?(r(I),a(v)):"false"===$&&f?(r(v),a(I)):(r(I),r(v));const b="true"===await i(n),h=m&&f&&"true"===$;e.setItem(`${n}-pdf-implicit-dv-feature-enabled`,h.toString()),c({enableImplicitDefaultViewershipFeature:h,isAcrobatDefaultForSurface:b,toastMessage:o.getTranslation(`${n}ImplicitDVNotification`),fteToolTipStrings:{title:o.getTranslation(`${n}ImplicitDVFTEHeader`),description:o.getTranslation(`${n}ImplicitDVFTEBody`),button:o.getTranslation("closeButton")}})}export{n as implicitDefaultViewershipInit};