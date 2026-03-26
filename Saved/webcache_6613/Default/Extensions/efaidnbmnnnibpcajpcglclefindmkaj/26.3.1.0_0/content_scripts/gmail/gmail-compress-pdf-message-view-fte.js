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
const MESSAGE_VIEW_FTE_STORAGE_KEY="acrobat-gmail-message-view-compress-pdf-fte-config";class GmailCompressPDFMessageViewFte{id="GmailCompressPDFMessageViewFte";timeout=3e3;static GMAIL_DOMAINS=["mail.google.com"];constructor(){const e=window.location.hostname;if(!GmailCompressPDFMessageViewFte.GMAIL_DOMAINS.some(s=>e.includes(s)))return this.isEligible=async()=>!1,void(this.render=async()=>{});this.initPromise=this.loadServices()}async loadServices(){[this.fteUtils,this.gmailCompressPDFMessageViewFteService,this.state]=await Promise.all([import(chrome.runtime.getURL("content_scripts/utils/fte-utils.js")),import(chrome.runtime.getURL("content_scripts/gmail/gmail-compress-pdf-message-view-fte-service.js")),import(chrome.runtime.getURL("content_scripts/gmail/state.js"))])}async render(){await(this.gmailCompressPDFMessageViewFteService?.addFte?.())}async isEligible(){const e=await chrome.runtime.sendMessage({main_op:"gmail-message-view-compress-pdf-init"});if(!e?.enableGmailMessageViewCompressPDFTouchPoint||!e?.enableFte)return!1;await this.initPromise;const s=this.state?.default,t=s?.compressPdfMessageViewFteState?.shadowHostForFTE;if(!t)return!1;const i=await(this.fteUtils?.initFteStateAndConfig?.(MESSAGE_VIEW_FTE_STORAGE_KEY)),a=e?.fteConfig;return await(this.fteUtils?.shouldShowFteTooltip?.(a,i,e.enableFte))}}