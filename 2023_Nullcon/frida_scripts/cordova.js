Java.perform(function() {
    // https://developer.android.com/reference/android/webkit/WebView
    var Webview = Java.use("android.webkit.WebView")
    Webview.loadUrl.overload("java.lang.String").implementation = function(url) {
        console.log("\nWebView.loadUrl()");
        console.log("> URL: " + url);

        this.setWebContentsDebuggingEnabled(true);
        this.loadUrl(url);
    }
});