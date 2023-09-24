Java.perform(function() {
    // https://android.googlesource.com/platform/external/conscrypt/+/1186465/src/platform/java/org/conscrypt/TrustManagerImpl.java
    var ArrayList = Java.use("java.util.ArrayList");
    var TrustManagerImpl = Java.use("com.android.org.conscrypt.TrustManagerImpl");
    TrustManagerImpl.checkTrustedRecursive.overload('[Ljava.security.cert.X509Certificate;', '[B', '[B', 'java.lang.String', 'boolean', 'java.util.ArrayList', 'java.util.ArrayList', 'java.util.Set').implementation = function(certs, ocspData, tlsSctData, host, clientAuth, untrustedChain, trustAnchorChain, used) {
        console.log("\nTrustManagerImpl.checkTrustedRecursive()");
        console.log("> Host: " + host);
        return ArrayList.$new();
    }
});