<script lang="ts">
  import qrcode from "qrcode-generator";
  import { SHARED_SECRET, SERVICE, EMAIL } from "../lib/config";

  const qs = new URLSearchParams({
    secret: SHARED_SECRET,
    issuer: SERVICE,
    algorithm: "SHA1",
    digits: "6",
    period: "30",
  }).toString();

  const url = `otpauth://totp/${SERVICE}:${EMAIL}?${qs}`;

  const qr = qrcode(0, "M");
  qr.addData(url);
  qr.make();
</script>

<h2>What's in a TOTP QR code</h2>
<p>
  Scan the QR code with Google Authenticator, another authenticator app, or even
  with the&nbsp;iOS Camera app.
</p>
<div class="layout">
  <div class="qr">
    {@html qr.createSvgTag(8)}
  </div>
  <div class="table">
    <dl>
      <dt>URL:</dt>
      <dd class="url">
        <pre><code
            >{url.split("?")[0]}<br />   ?{@html qs
              .split("&")
              .join("<br/>   &")}</code
          ></pre>
      </dd>
      <dt>Email:</dt>
      <dd>{EMAIL}</dd>
      <dt>Service:</dt>
      <dd>{SERVICE}</dd>
      <dt>Secret (Base32-encoded):</dt>
      <dd>{SHARED_SECRET}</dd>
      <dt>Algorithm:</dt>
      <dd>SHA-1 (default)</dd>
      <dt>Digits:</dt>
      <dd>6 (default)</dd>
    </dl>
  </div>
</div>

<style>
  .layout {
    display: grid;
    grid-template-columns: auto 1fr;
    align-items: center;
    gap: 5rem;
    max-width: 80%;
    overflow: hidden;
  }

  .table {
    font-size: 1.375rem;
    text-align: left;
  }

  dt:not(:first-of-type) {
    margin-top: 1em;
  }

  dd {
    word-break: break-word;
    overflow-wrap: break-word;
  }

  .url {
    pre {
      font-size: 1.375rem;
      margin: 0;
    }
  }
</style>
