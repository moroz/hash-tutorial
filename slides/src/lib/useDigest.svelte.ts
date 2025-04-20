export default function useDigest(secret: Uint8Array, step: Uint8Array) {
  let key: CryptoKey | null = $state(null);
  let msg = $state(step);

  $effect.pre(() => {
    window.crypto.subtle
      .importKey(
        "raw",
        secret,
        {
          name: "HMAC",
          hash: { name: "SHA-1" },
        },
        false,
        ["sign", "verify"],
      )
      .then((k) => {
        key = k;
      });
  });

  let digest = $state(new Uint8Array(20));

  $effect(() => {
    if (!key) return;
    crypto.subtle.sign("HMAC", key, msg).then((d) => {
      digest = new Uint8Array(d);
    });
  });

  return {
    get ready() {
      return !!key;
    },
    get digest() {
      return digest;
    },
    update(step: Uint8Array) {
      msg = step;
    },
  };
}
