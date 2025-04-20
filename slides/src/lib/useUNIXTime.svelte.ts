export default function useUNIXTime() {
  let time = $state(Math.floor(Date.now() / 1000));

  $effect(() => {
    const interval = setInterval(() => {
      time = Math.floor(Date.now() / 1000);
    }, 1000);

    return () => {
      clearInterval(interval);
    };
  });

  return {
    get time() {
      return time;
    },
    get timeStep() {
      return Math.floor(time / 30);
    },
    get timeStepEncoded() {
      const buf = new ArrayBuffer(8);
      const view = new DataView(buf);
      const T = Math.floor(time / 30);
      view.setUint32(4, T, false);
      return new Uint8Array(buf);
    },
  };
}
