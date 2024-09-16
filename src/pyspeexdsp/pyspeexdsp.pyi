"""SpeexDSP"""

class EchoCanceller:
    def __init__(
        self,
        frame_size: int = 512,
        filter_length: int = 2048,
        sample_rate: int = 16000,
        mics: int = 1,
        speakers: int = 1
    ) -> None:
        """
        Constructor for the EchoCanceller class.

        Args:
            frame_size (int): The size of the frame.
            filter_length (int): The length of the filter.
            sample_rate (int): The sampling rate.
            mics (int): The number of microphones.
            speakers (int): The number of speakers.
        """
        ...

    def process(self, near: bytes, far: bytes) -> bytes:
        """
        Processes audio data for echo cancellation.

        Args:
            near (bytes): The near-end audio data.
            far (bytes): The far-end audio data.

        Returns:
            bytes: The processed audio data.
        """
        ...

    def set_echo_suppress(self, level: int) -> None:
        """
        Sets the echo suppression level.

        Args:
            level (int): The level of echo suppression to apply.
        """
        ...

    def enable_echo_suppression(self, enable: bool) -> None:
        """
        Enables or disables echo suppression.

        Args:
            enable (bool): If True, enables echo suppression; if False, disables it.
        """
        ...
