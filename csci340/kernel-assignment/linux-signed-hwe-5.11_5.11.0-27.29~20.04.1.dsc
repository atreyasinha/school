-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA256

Format: 3.0 (native)
Source: linux-signed-hwe-5.11
Binary: linux-image-5.11.0-27-generic, linux-image-5.11.0-27-lowlatency, linux-image-5.11.0-27-generic-64k, kernel-signed-image-5.11.0-27-generic-di, linux-image-5.11.0-27-generic-dbgsym, linux-image-5.11.0-27-lowlatency-dbgsym, linux-image-5.11.0-27-generic-64k-dbgsym
Architecture: amd64 arm64 ppc64el s390x
Version: 5.11.0-27.29~20.04.1
Maintainer: Canonical Kernel Team <kernel-team@lists.ubuntu.com>
Standards-Version: 3.9.4
Build-Depends: debhelper (>= 9), lsb-release, python3, python3-apt
Build-Depends-Arch: sbsigntool [amd64 arm64], linux-hwe-5.11-headers-5.11.0-27 (>= 5.11.0-27.29~20.04.1), linux-headers-5.11.0-27-generic (>= 5.11.0-27.29~20.04.1)
Package-List:
 kernel-signed-image-5.11.0-27-generic-di udeb debian-installer extra arch=amd64,arm64,ppc64el,s390x
 linux-image-5.11.0-27-generic deb kernel optional arch=amd64,arm64,ppc64el,s390x
 linux-image-5.11.0-27-generic-64k deb kernel optional arch=arm64
 linux-image-5.11.0-27-generic-64k-dbgsym deb devel optional arch=arm64
 linux-image-5.11.0-27-generic-dbgsym deb devel optional arch=amd64,arm64,ppc64el,s390x
 linux-image-5.11.0-27-lowlatency deb kernel optional arch=amd64
 linux-image-5.11.0-27-lowlatency-dbgsym deb devel optional arch=amd64
Checksums-Sha1:
 cebe68e3a92330cc7c616355e1844ea8fcddfd6b 19688 linux-signed-hwe-5.11_5.11.0-27.29~20.04.1.tar.xz
Checksums-Sha256:
 c8a16d4ecb5fb378e5a45fd007805b22e42959d8cc3c9943e8b611d517d75aa4 19688 linux-signed-hwe-5.11_5.11.0-27.29~20.04.1.tar.xz
Files:
 501e38d54bcf63944821b113917009ca 19688 linux-signed-hwe-5.11_5.11.0-27.29~20.04.1.tar.xz

-----BEGIN PGP SIGNATURE-----

iQEzBAEBCAAdFiEE8u2tbvu5Bl/TA9thRqrzNXDhFisFAmET8lUACgkQRqrzNXDh
FitvkAf6A2N25BZc1sPxr5ilIw5GKUOnX+ZomvS62avLqyhWEqeMLEBWWjhDobw1
oh4yWAyomM2Vi1g8Z5oBw++m/C+Q8qEHUtCpQBHeG3Kl762C+nWbtQKyIwJeLX+Y
CuOFzeKW7ph/5jNElDk2R229OfQxtR/th25h1hs3lf/BLJ/h17NJKaw0ca445SC/
HgPsGjBriWaHXFeNoHywGIQdbpkZf5Wqc301padlDbMxoYOVunYvaDs9KLDMwcW5
XGJkUi/X7olCkiqyiMwOy6EsjVx+2okTo+C82P0WLhs8CZoq3VCw2zXPxmRN22gY
K8IvgwW0416mr4WylDgOXsr8AJ8ykA==
=rIqJ
-----END PGP SIGNATURE-----
