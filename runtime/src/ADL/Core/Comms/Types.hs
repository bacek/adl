{-# LANGUAGE Rank2Types #-}
module ADL.Core.Comms.Types(
  SinkConnection,
  send,
  LocalSink,
  toSink,
  EndPoint,
  newLocalSink
  ) where

-- export only the public bits of Internals

import ADL.Core.Comms.Types.Internals